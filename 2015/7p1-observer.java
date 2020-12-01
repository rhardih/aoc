import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Observable;
import java.util.Observer;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

interface SignalProvider {
  public int getSignal();
}

class SignalInput extends Observable implements SignalProvider {
  private int signal;

  public int getSignal() {
    return this.signal;
  }

  public void setSignal(int signal) {
    this.signal = signal;

    setChanged();
    notifyObservers();
  }
}

class Wire extends Observable implements SignalProvider, Observer {
  private String identifier;
  private int signal;

  public Wire(String identifier) {
    this.identifier = identifier;
    this.signal = -1;
  }

  public String getIdentifier() {
    return identifier;
  }

  public int getSignal() {
    return signal;
  }

  public void setSignal(int signal) {
    this.signal = signal;

    setChanged();
    notifyObservers();
  }

  @Override
  public void update(Observable observable, Object arg) {
    SignalProvider signalProvider = (SignalProvider) observable;

    setSignal(signalProvider.getSignal());
  }
}

abstract class Gate extends Observable implements SignalProvider, Observer {
  private int signal;

  public int getSignal() {
    return signal;
  }

  public void setSignal(int signal) {
    this.signal = signal;

    setChanged();
    notifyObservers();
  }

  @Override
  public abstract void update(Observable observable, Object arg);
}

class AndGate extends Gate {
  private int firstInputSignal;

  public AndGate() {
    this.firstInputSignal = -1;
  }

  @Override
  public void update(Observable observable, Object arg) {
    SignalProvider signalProvider = (SignalProvider) observable;
    int inputSignal = signalProvider.getSignal();

    if (this.firstInputSignal == -1) {
      this.firstInputSignal = inputSignal;
    } else {
      setSignal((this.firstInputSignal & inputSignal));
    }
  }
}

class OrGate extends Gate {
  private int firstInputSignal;

  public OrGate() {
    this.firstInputSignal = -1;
  }

  @Override
  public void update(Observable observable, Object arg) {
    SignalProvider signalProvider = (SignalProvider) observable;
    int inputSignal = signalProvider.getSignal();

    if (this.firstInputSignal == -1) {
      this.firstInputSignal = inputSignal;
    } else {
      setSignal((this.firstInputSignal | inputSignal));
    }
  }
}

class LeftShiftGate extends Gate {
  private int positions;

  public LeftShiftGate(int positions) {
    this.positions = positions;
  }

  @Override
  public void update(Observable observable, Object arg) {
    SignalProvider signalProvider = (SignalProvider) observable;
    int inputSignal = signalProvider.getSignal();

    setSignal((inputSignal << this.positions));
  }
}

class RightShiftGate extends Gate {
  private int positions;

  public RightShiftGate(int positions) {
    this.positions = positions;
  }

  @Override
  public void update(Observable observable, Object arg) {
    SignalProvider signalProvider = (SignalProvider) observable;
    int inputSignal = signalProvider.getSignal();

    setSignal((inputSignal >> this.positions));
  }
}

class NotGate extends Gate {
  @Override
  public void update(Observable observable, Object arg) {
    SignalProvider signalProvider = (SignalProvider) observable;
    int inputSignal = signalProvider.getSignal();

    setSignal(~inputSignal);
  }
}

interface Instruction {
  void performOn(Circuit circuit);
}

class SignalImmediateInstruction implements Instruction {
  private String outputWireIdentifier;
  private int signal;
  private SignalInput signalInput;

  public SignalImmediateInstruction(String outputWireIdentifier, int signal) {
    this.outputWireIdentifier = outputWireIdentifier;
    this.signal = signal;
    this.signalInput = new SignalInput();
  }

  public void performOn(Circuit circuit) {
    Wire outputWire = circuit.getWire(this.outputWireIdentifier);

    this.signalInput.addObserver(outputWire);
  }

  public void trigger() {
    this.signalInput.setSignal(this.signal);
  }
}

class SignalWireInstruction implements Instruction {
  private String inputWireIdentifier;
  private String outputWireIdentifier;

  public SignalWireInstruction(String inputWireIdentifier, String outputWireIdentifier) {
    this.inputWireIdentifier = inputWireIdentifier;
    this.outputWireIdentifier = outputWireIdentifier;
  }

  public void performOn(Circuit circuit) {
    Wire inputWire = circuit.getWire(this.inputWireIdentifier);
    Wire outputWire = circuit.getWire(this.outputWireIdentifier);

    inputWire.addObserver(outputWire);
  }
}

class AndInstruction implements Instruction {
  private String inputWireIdentifier0;
  private String inputWireIdentifier1;
  private String outputWireIdentifier;

  public AndInstruction(
      String inputWireIdentifier0, String inputWireIdentifier1, String outputWireIdentifier) {

    this.inputWireIdentifier0 = inputWireIdentifier0;
    this.inputWireIdentifier1 = inputWireIdentifier1;
    this.outputWireIdentifier = outputWireIdentifier;
  }

  public void performOn(Circuit circuit) {
    Wire inputWire0 = circuit.getWire(this.inputWireIdentifier0);
    Wire inputWire1 = circuit.getWire(this.inputWireIdentifier1);
    Wire outputWire = circuit.getWire(this.outputWireIdentifier);
    AndGate andGate = new AndGate();

    inputWire0.addObserver(andGate);
    inputWire1.addObserver(andGate);
    andGate.addObserver(outputWire);
  }
}

class AndImmediateInstruction implements Instruction {
  private String inputWireIdentifier;
  private String outputWireIdentifier;
  private int signal;

  public AndImmediateInstruction(
      String inputWireIdentifier, String outputWireIdentifier, int signal) {
    this.inputWireIdentifier = inputWireIdentifier;
    this.outputWireIdentifier = outputWireIdentifier;
    this.signal = signal;
  }

  public void performOn(Circuit circuit) {
    Wire inputWire = circuit.getWire(this.inputWireIdentifier);
    Wire outputWire = circuit.getWire(this.outputWireIdentifier);
    SignalInput signalInput = new SignalInput();
    AndGate andGate = new AndGate();

    signalInput.addObserver(andGate);
    inputWire.addObserver(andGate);
    andGate.addObserver(outputWire);

    signalInput.setSignal(this.signal);
  }
}

class OrInstruction implements Instruction {
  private String inputWireIdentifier0;
  private String inputWireIdentifier1;
  private String outputWireIdentifier;

  public OrInstruction(
      String inputWireIdentifier0, String inputWireIdentifier1, String outputWireIdentifier) {
    this.inputWireIdentifier0 = inputWireIdentifier0;
    this.inputWireIdentifier1 = inputWireIdentifier1;
    this.outputWireIdentifier = outputWireIdentifier;
  }

  public void performOn(Circuit circuit) {
    Wire inputWire0 = circuit.getWire(this.inputWireIdentifier0);
    Wire inputWire1 = circuit.getWire(this.inputWireIdentifier1);
    Wire outputWire = circuit.getWire(this.outputWireIdentifier);
    OrGate orGate = new OrGate();

    inputWire0.addObserver(orGate);
    inputWire1.addObserver(orGate);
    orGate.addObserver(outputWire);
  }
}

class leftShiftInstruction implements Instruction {
  private String inputWireIdentifier;
  private String outputWireIdentifier;
  private int positions;

  public leftShiftInstruction(
      String inputWireIdentifier, String outputWireIdentifier, int positions) {
    this.inputWireIdentifier = inputWireIdentifier;
    this.outputWireIdentifier = outputWireIdentifier;
    this.positions = positions;
  }

  public void performOn(Circuit circuit) {
    Wire inputWire = circuit.getWire(this.inputWireIdentifier);
    Wire outputWire = circuit.getWire(this.outputWireIdentifier);
    LeftShiftGate leftShiftGate = new LeftShiftGate(this.positions);

    inputWire.addObserver(leftShiftGate);
    leftShiftGate.addObserver(outputWire);
  }
}

class rightShiftInstruction implements Instruction {
  private String inputWireIdentifier;
  private String outputWireIdentifier;
  private int positions;

  public rightShiftInstruction(
      String inputWireIdentifier, String outputWireIdentifier, int positions) {
    this.inputWireIdentifier = inputWireIdentifier;
    this.outputWireIdentifier = outputWireIdentifier;
    this.positions = positions;
  }

  public void performOn(Circuit circuit) {
    Wire inputWire = circuit.getWire(this.inputWireIdentifier);
    Wire outputWire = circuit.getWire(this.outputWireIdentifier);
    RightShiftGate rightShiftGate = new RightShiftGate(this.positions);

    inputWire.addObserver(rightShiftGate);
    rightShiftGate.addObserver(outputWire);
  }
}

class NotInstruction implements Instruction {
  private String inputWireIdentifier;
  private String outputWireIdentifier;

  public NotInstruction(String inputWireIdentifier, String outputWireIdentifier) {
    this.inputWireIdentifier = inputWireIdentifier;
    this.outputWireIdentifier = outputWireIdentifier;
  }

  public void performOn(Circuit circuit) {
    Wire inputWire = circuit.getWire(this.inputWireIdentifier);
    Wire outputWire = circuit.getWire(this.outputWireIdentifier);
    NotGate notGate = new NotGate();

    inputWire.addObserver(notGate);
    notGate.addObserver(outputWire);
  }
}

class InstructionFactory {
  public static Instruction getInstruction(Circuit circuit, String instruction) {
    // Patterns
    Pattern andImmediatePattern = Pattern.compile("^(\\d+) AND ([a-z]+) -> ([a-z]+)$");
    Pattern andPattern = Pattern.compile("^([a-z]+) AND ([a-z]+) -> ([a-z]+)$");
    Pattern leftShiftPattern = Pattern.compile("^([a-z]+) LSHIFT (\\d+) -> ([a-z]+)$");
    Pattern notPattern = Pattern.compile("^NOT ([a-z]+) -> ([a-z]+)$");
    Pattern orPattern = Pattern.compile("^([a-z]+) OR ([a-z]+) -> ([a-z]+)$");
    Pattern rightShiftPattern = Pattern.compile("^([a-z]+) RSHIFT (\\d+) -> ([a-z]+)$");
    Pattern signalImmediatePattern = Pattern.compile("^(\\d+) -> ([a-z]+)$");
    Pattern signalWirePattern = Pattern.compile("^([a-z]+) -> ([a-z]+)$");

    // Matchers
    Matcher andImmediateMatcher = andImmediatePattern.matcher(instruction);
    Matcher andMatcher = andPattern.matcher(instruction);
    Matcher leftShiftMatcher = leftShiftPattern.matcher(instruction);
    Matcher notMatcher = notPattern.matcher(instruction);
    Matcher orMatcher = orPattern.matcher(instruction);
    Matcher rightShiftMatcher = rightShiftPattern.matcher(instruction);
    Matcher signalImmediateMatcher = signalImmediatePattern.matcher(instruction);
    Matcher signalWireMatcher = signalWirePattern.matcher(instruction);

    if (signalImmediateMatcher.find()) {
      return new SignalImmediateInstruction(
          signalImmediateMatcher.group(2), Short.parseShort(signalImmediateMatcher.group(1)));
    } else if (signalWireMatcher.find()) {
      return new SignalWireInstruction(signalWireMatcher.group(1), signalWireMatcher.group(2));
    } else if (andMatcher.find()) {
      return new AndInstruction(andMatcher.group(1), andMatcher.group(2), andMatcher.group(3));
    } else if (andImmediateMatcher.find()) {
      return new AndImmediateInstruction(
          andImmediateMatcher.group(2),
          andImmediateMatcher.group(3),
          Short.parseShort(andImmediateMatcher.group(1)));
    } else if (orMatcher.find()) {
      return new OrInstruction(orMatcher.group(1), orMatcher.group(2), orMatcher.group(3));
    } else if (leftShiftMatcher.find()) {
      return new leftShiftInstruction(
          leftShiftMatcher.group(1),
          leftShiftMatcher.group(3),
          Short.parseShort(leftShiftMatcher.group(2)));
    } else if (rightShiftMatcher.find()) {
      return new rightShiftInstruction(
          rightShiftMatcher.group(1),
          rightShiftMatcher.group(3),
          Short.parseShort(rightShiftMatcher.group(2)));
    } else if (notMatcher.find()) {
      return new NotInstruction(notMatcher.group(1), notMatcher.group(2));
    }

    return null;
  }
}

class Circuit {
  private HashMap<String, Wire> wires;

  public Circuit() {
    this.wires = new HashMap<String, Wire>();
  }

  // Get existing or create and return a new wire for the circuit.
  public Wire getWire(String identifier) {
    Wire wire;

    if (this.wires.containsKey(identifier)) {
      wire = this.wires.get(identifier);
    } else {
      wire = new Wire(identifier);
      wires.put(identifier, wire);
    }

    return wire;
  }

  public String getWireSignal(String wireIdentifier) {
    return String.valueOf(wires.get(wireIdentifier).getSignal());
  }
}

class SomeAssemblyRequired {
  public static void main(String[] args) {
    Circuit circuit = new Circuit();
    Scanner scanner = new Scanner(System.in);
    List<SignalImmediateInstruction> signalImmediateInstructions =
        new ArrayList<SignalImmediateInstruction>();

    while (scanner.hasNext()) {
      Instruction instruction = InstructionFactory.getInstruction(circuit, scanner.nextLine());

      instruction.performOn(circuit);

      if (instruction instanceof SignalImmediateInstruction) {
        signalImmediateInstructions.add((SignalImmediateInstruction) instruction);
      }
    }

    scanner.close();

    // To run the circuit we trigger all direct value assignments, which should
    // in turn trigger its dependents, and so on and so forth.
    for (SignalImmediateInstruction instruction : signalImmediateInstructions) {
      instruction.trigger();
    }

    System.out.println("Signal ultimately provided to wire a: " + circuit.getWireSignal("a"));
  }
}
