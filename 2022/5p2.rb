=begin

As you watch the crane operator expertly rearrange the crates, you notice the
process isn't following your prediction.

Some mud was covering the writing on the side of the crane, and you quickly
wipe it away. The crane isn't a CrateMover 9000 - it's a CrateMover 9001.

The CrateMover 9001 is notable for many new and exciting features: air
conditioning, leather seats, an extra cup holder, and the ability to pick up
and move multiple crates at once.

Again considering the example above, the crates begin in the same
configuration:

    [D]    
[N] [C]    
[Z] [M] [P]
 1   2   3 

Moving a single crate from stack 2 to stack 1 behaves the same as before:

[D]        
[N] [C]    
[Z] [M] [P]
 1   2   3 

However, the action of moving three crates from stack 1 to stack 3 means that
those three moved crates stay in the same order, resulting in this new
configuration:

        [D]
        [N]
    [C] [Z]
    [M] [P]
 1   2   3

Next, as both crates are moved from stack 2 to stack 1, they retain their order
as well:

        [D]
        [N]
[C]     [Z]
[M]     [P]
 1   2   3

Finally, a single crate is still moved from stack 1 to stack 2, but now it's
crate C that gets moved:

        [D]
        [N]
        [Z]
[M] [C] [P]
 1   2   3

In this example, the CrateMover 9001 has put the crates in a totally different
order: MCD.

Before the rearrangement process finishes, update your simulation so that the
Elves know where they should stand to be ready to unload the final supplies.
After the rearrangement procedure completes, what crate ends up on top of each
stack?

=end

stacks = {
	"1" => ["D", "L", "J", "R", "V", "G", "F"],
	"2" => ["T", "P", "M", "B", "V", "H", "J", "S"],
	"3" => ["V", "H", "M", "F", "D", "G", "P", "C"],
	"4" => ["M", "D", "P", "N", "G", "Q"],
	"5" => ["J", "L", "H", "N", "F"],
	"6" => ["N", "F", "V", "Q", "D", "G", "T", "Z"],
	"7" => ["F", "D", "B", "L"],
	"8" => ["M", "J", "B", "S", "V", "D", "N"],
	"9" => ["G", "L", "D"],
}

STDIN.read.split("\n").each do |line|
  next unless line =~ /move/

  count, from, to  = line.scan(/move (\d+) from (\d+) to (\d+)/).first

  tmp = stacks[from].pop(count.to_i)
  stacks[to].push(*tmp)
end

top_crates = stacks.reduce("") do |acc, el|
  _, crates = el

  acc << crates.pop
end

puts "Crates at the top of each stack after rearrangement: #{top_crates}"
