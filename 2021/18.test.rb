require_relative "18"

# Pair#explodees tests
{
  Pair.new([[[[4, 0], [5, 4]], [[7, 7], [6, 0]]], [[8, 9], [[[5, 6], 9], [11, 0]]]]) => [Pair.new([5, 6])]
}.each do |node, expected_result|
  tmp0 = node.explodees.map(&:to_a)
  tmp1 = expected_result.map(&:to_a)

  unless tmp0.eql?(tmp1)
    raise "explodees of #{node}: expected: #{tmp1}, got: #{tmp0}"
  end
end

# Pair#explode tests
{
  Pair.new([[[[[9,8],1],2],3],4]) => Pair.new([[[[0,9],2],3],4]),
	Pair.new([7,[6,[5,[4,[3,2]]]]]) => Pair.new([7,[6,[5,[7,0]]]]),
	Pair.new([[6,[5,[4,[3,2]]]],1]) => Pair.new([[6,[5,[7,0]]],3]),
  Pair.new([[3,[2,[1,[7,3]]]],[6,[5,[4,[3,2]]]]]) => Pair.new([[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]]),
  Pair.new([[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]]) => Pair.new([[3,[2,[8,0]]],[9,[5,[7,0]]]]),
  Pair.new([[[[[4,3],4],4],[7,[[8,4],9]]],[1,1]]) => Pair.new([[[[0,7],4],[7,[[8,4],9]]],[1,1]]),
  Pair.new([[[[[1, 1], [2, 2]], [3, 3]], [4, 4]], [5,5]]) => Pair.new([[[[0, [3, 2]], [3, 3]], [4, 4]], [5,5]]),
  Pair.new([[[[4, 0], [5, 4]], [[7, 7], [6, 0]]], [[8, 9], [[[5, 6], 9], [[5, 6], 0]]]]) => Pair.new([[[[4, 0], [5, 4]], [[7, 7], [6, 0]]], [[8, 14], [[0, 15], [[5, 6], 0]]]]),
  Pair.new([[[[4, 0], [5, 4]], [[7, 7], [6, 0]]], [[8, 14], [[0, 15], [[5, 6], 0]]]]) => Pair.new([[[[4, 0], [5, 4]], [[7, 7], [6, 0]]], [[8, 14], [[0, 20], [0, 6]]]]),
}.each do |node, expected_explosion|
  tmp = Marshal.load(Marshal.dump(node))
  tmp.explodees.first.explode!

  unless tmp.eql?(expected_explosion)
    raise "explosion of #{node}: expected: #{expected_explosion}, got: #{tmp}"
  end
end

# Pair#split tests
{
  Pair.new([[[[4, 0], [5, 4]], [[7, 7], [6, 0]]], [[8, 14], [[0, 20], [0, 6]]]]) => Pair.new([[[[4, 0], [5, 4]], [[7, 7], [6, 0]]], [[8, [7, 7]], [[0, 20], [0, 6]]]]),
  Pair.new([[[[4, 0], [5, 4]], [[7, 7], [6, 0]]], [[8, [7, 7]], [[0, 20], [0, 6]]]]) => Pair.new([[[[4, 0], [5, 4]], [[7, 7], [6, 0]]], [[8, [7, 7]], [[0, [10, 10]], [0, 6]]]]),
}.each do |node, expected_split|
  tmp = Marshal.load(Marshal.dump(node))
  tmp.splitees.first.split!

  unless tmp.eql?(expected_split)
    raise "explosion of #{node}: expected: #{expected_split}, got: #{tmp}"
  end
end

# Pair#+ tests
{
  [
    Pair.new([[[[4,3],4],4],[7,[[8,4],9]]]),
    Pair.new([1,1]),
  ] => Pair.new([[[[0,7],4],[[7,8],[6,0]]],[8,1]]),
  [
    Pair.new([1,1]),
    Pair.new([2,2]),
    Pair.new([3,3]),
    Pair.new([4,4]),
  ] => Pair.new([[[[1,1],[2,2]],[3,3]],[4,4]]),
  [
    Pair.new([1,1]),
    Pair.new([2,2]),
    Pair.new([3,3]),
    Pair.new([4,4]),
    Pair.new([5,5]),
  ] => Pair.new([[[[3,0],[5,3]],[4,4]],[5,5]]),
  [
    Pair.new([1,1]),
    Pair.new([2,2]),
    Pair.new([3,3]),
    Pair.new([4,4]),
    Pair.new([5,5]),
    Pair.new([6,6]),
  ] => Pair.new([[[[5,0],[7,4]],[5,5]],[6,6]]),
  [
    Pair.new([[[0,[4,5]],[0,0]],[[[4,5],[2,6]],[9,5]]]),
    Pair.new([7,[[[3,7],[4,3]],[[6,3],[8,8]]]]),
    Pair.new([[2,[[0,8],[3,4]]],[[[6,7],1],[7,[1,6]]]]),
    Pair.new([[[[2,4],7],[6,[0,5]]],[[[6,8],[2,8]],[[2,1],[4,5]]]]),
    Pair.new([7,[5,[[3,8],[1,4]]]]),
    Pair.new([[2,[2,2]],[8,[8,1]]]),
    Pair.new([2,9]),
    Pair.new([1,[[[9,3],9],[[9,0],[0,7]]]]),
    Pair.new([[[5,[7,4]],7],1]),
    Pair.new([[[[4,2],2],6],[8,7]]),
  ] => Pair.new([[[[8,7],[7,7]],[[8,6],[7,7]]],[[[0,7],[6,6]],[8,7]]]),
}.each do |list, expected_result|
  result = list.reduce do |node0, node1|
    node0 + node1
  end

  unless result.eql?(expected_result)
    raise "Addition of #{list.join(' + ')}: expected: #{expected_result}, got: #{result}"
  end
end

# Pair#magnitude
{
  Pair.new([9,1]) => 29,
  Pair.new([1,9]) => 21,
  Pair.new([[9,1],[1,9]]) => 129,
  Pair.new([[1,2],[[3,4],5]]) => 143,
  Pair.new([[[[0,7],4],[[7,8],[6,0]]],[8,1]]) => 1384,
  Pair.new([[[[1,1],[2,2]],[3,3]],[4,4]]) => 445,
  Pair.new([[[[3,0],[5,3]],[4,4]],[5,5]]) => 791,
  Pair.new([[[[5,0],[7,4]],[5,5]],[6,6]]) => 1137,
  Pair.new([[[[8,7],[7,7]],[[8,6],[7,7]]],[[[0,7],[6,6]],[8,7]]]) => 3488
}.each do |node, expected_magnitude|
  tmp = node.magnitude

  unless tmp == expected_magnitude
    raise "Magnitude of #{node}: expected: #{expected_magnitude}, got: #{tmp}"
  end
end

puts "All tests passed!"
