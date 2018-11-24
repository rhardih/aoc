package main

import (
	"bufio"
	"fmt"
	"os"
	"regexp"
	"strconv"
	"sync"
)

var (
	circuit      = map[string]chan uint16{}
	circuitMutex = sync.RWMutex{}
	wg           = sync.WaitGroup{}
	done         = make(chan struct{})
)

func addWire(identifier string) {
	circuitMutex.Lock()
	if _, ok := circuit[identifier]; !ok {
		circuit[identifier] = make(chan uint16)
	}
	circuitMutex.Unlock()
}

func setSignal(identifier string, value uint16) {
	circuitMutex.RLock()
	wire, ok := circuit[identifier]
	circuitMutex.RUnlock()

	if !ok {
		fmt.Println("Wire not set up for", identifier)
		os.Exit(-1)
	}

	wg.Add(1)
	go func() {
		defer wg.Done()
		for {
			select {
			case wire <- value:
			case <-done:
				return
			}
		}
	}()
}

func getSignal(identifier string) uint16 {
	circuitMutex.RLock()
	wire := circuit[identifier]
	circuitMutex.RUnlock()

	tmp := <-wire

	return tmp
}

func main() {
	var (
		signal      = regexp.MustCompile(`^(\d+) -> ([a-z]+)$`)
		passthrough = regexp.MustCompile(`^([a-z]+) -> ([a-z]+)$`)
		andWire     = regexp.MustCompile(`^([a-z]+) AND ([a-z]+) -> ([a-z]+)$`)
		andValue    = regexp.MustCompile(`^(\d+) AND ([a-z]+) -> ([a-z]+)$`)
		or          = regexp.MustCompile(`^([a-z]+) OR ([a-z]+) -> ([a-z]+)$`)
		lshift      = regexp.MustCompile(`^([a-z]+) LSHIFT (\d+) -> ([a-z]+)$`)
		rshift      = regexp.MustCompile(`^([a-z]+) RSHIFT (\d+) -> ([a-z]+)$`)
		not         = regexp.MustCompile(`^NOT ([a-z]+) -> ([a-z]+)$`)
	)

	scanner := bufio.NewScanner(os.Stdin)

	for scanner.Scan() {
		instruction := scanner.Text()

		switch {
		case signal.MatchString(instruction):
			res := signal.FindStringSubmatch(instruction)
			value64, err := strconv.Atoi(res[1])
			if err != nil {
				os.Exit(-1)
			}

			outputId := res[2]

			if outputId == "b" {
				value64 = 16076
			}

			addWire(outputId)
			setSignal(outputId, uint16(value64))

		case passthrough.MatchString(instruction):
			res := passthrough.FindStringSubmatch(instruction)

			inputId0 := res[1]
			outputId := res[2]

			addWire(inputId0)
			addWire(outputId)

			go func() {
				signal0 := getSignal(inputId0)

				setSignal(outputId, signal0)
			}()

		case andWire.MatchString(instruction):
			res := andWire.FindStringSubmatch(instruction)
			inputId0 := res[1]
			inputId1 := res[2]
			outputId := res[3]

			addWire(inputId0)
			addWire(inputId1)
			addWire(outputId)

			go func() {
				signal0 := getSignal(inputId0)
				signal1 := getSignal(inputId1)

				setSignal(outputId, signal0&signal1)
			}()

		case andValue.MatchString(instruction):
			res := andValue.FindStringSubmatch(instruction)
			value64, err := strconv.Atoi(res[1])
			if err != nil {
				os.Exit(-1)
			}

			inputId0 := res[2]
			outputId := res[3]

			addWire(inputId0)
			addWire(outputId)

			go func() {
				signal0 := getSignal(inputId0)

				setSignal(outputId, uint16(value64)&signal0)
			}()

		case or.MatchString(instruction):
			res := or.FindStringSubmatch(instruction)
			inputId0 := res[1]
			inputId1 := res[2]
			outputId := res[3]

			addWire(inputId0)
			addWire(inputId1)
			addWire(outputId)

			go func() {
				signal0 := getSignal(inputId0)
				signal1 := getSignal(inputId1)

				setSignal(outputId, signal0|signal1)
			}()

		case lshift.MatchString(instruction):
			res := lshift.FindStringSubmatch(instruction)
			inputId0 := res[1]
			outputId := res[3]

			value64, err := strconv.Atoi(res[2])
			if err != nil {
				os.Exit(-1)
			}

			addWire(inputId0)
			addWire(outputId)

			go func() {
				signal0 := getSignal(inputId0)

				setSignal(outputId, signal0<<uint16(value64))
			}()

		case rshift.MatchString(instruction):
			res := rshift.FindStringSubmatch(instruction)
			inputId0 := res[1]
			outputId := res[3]

			value64, err := strconv.Atoi(res[2])
			if err != nil {
				os.Exit(-1)
			}

			addWire(inputId0)
			addWire(outputId)

			go func() {
				signal0 := getSignal(inputId0)

				setSignal(outputId, signal0>>uint16(value64))
			}()

		case not.MatchString(instruction):
			res := not.FindStringSubmatch(instruction)
			inputId0 := res[1]
			outputId := res[2]

			addWire(inputId0)
			addWire(outputId)

			go func() {
				signal0 := getSignal(inputId0)

				setSignal(outputId, ^signal0)
			}()

		default:
			fmt.Println("Unknown instruction:", instruction)
		}
	}

	//for k, v := range circuit {
	//  fmt.Printf("%s: %d\n", k, <-v)
	//}

	fmt.Println("The signal ultimately on wire a is", <-circuit["a"])

	close(done)
	wg.Wait()
}
