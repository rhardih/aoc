# Snailfish number
class Pair
  attr_accessor :value, :parent, :left, :right

  def initialize(data, parent = nil)
    if data.is_a?(Integer)
      @value = data
    else
      l, r = data

      @left = Pair.new(l, self)
      @right = Pair.new(r, self)
    end

    @parent = parent
  end

  def root
    tmp = self

    tmp = tmp.parent until tmp.parent.nil?

    tmp
  end

  def is_right_child?
    !parent.nil? && parent.right == self
  end

  def inorder
    tmp = []

    tmp += left.inorder unless left.nil?
    tmp += [self]
    tmp += right.inorder unless right.nil?

    tmp
  end

  def height
    if left.nil? && right.nil?
      0
    elsif left.nil?
      1 + right.height
    elsif right.nil?
      1 + left.height
    else
      1 + [left.height, right.height].max
    end
  end

  def depth
    tmp = parent
    value = 0

    until tmp.nil?
      tmp = tmp.parent
      value += 1
    end

    value
  end

  # Returns all pairs in a number eligible for explosion
  def explodees
    tmp = []

    if depth == 4 && value.nil?
      tmp << self
    else
      tmp += left.explodees unless left.nil?
      tmp += right.explodees unless right.nil?
    end

    tmp
  end

  # Returns all pairs in a number eligible for splitting
  def splitees
    tmp = []

    if !value.nil? && value >= 10
      tmp << self
    else
      tmp += left.splitees unless left.nil?
      tmp += right.splitees unless right.nil?
    end

    tmp
  end

  def explode!
    tmp = root.inorder
    left_index = tmp.index(left)

    index = left_index - 1
    raise "Invalid index left" if index.nil?

    # Add the pairs left value to the first regular number to the left of the
    # exploding pair (if any)
    until index < 0
      unless tmp[index].value.nil? || left.value.nil?
        tmp[index].value += left.value
        break
      end

      index -= 1
    end

    right_index = tmp.index(right)

    index = right_index + 1
    raise "Invalid index right" if index.nil?

    # Add the pair's right value to the first regular number to the right of the
    # exploding pair (if any)
    until index > tmp.length - 1 # has no regular number to its right
      unless tmp[index].value.nil? || right.value.nil?
        tmp[index].value += right.value
        break
      end

      index += 1
    end

    # Replace the entire exploding pair with the regular number 0

    is_right_child? ? parent.right = Pair.new(0, parent) : parent.left = Pair.new(0, parent)
  end

  def split!
    @left = Pair.new((value / 2.0).floor, self)
    @right = Pair.new((value / 2.0).ceil, self)
    @value = nil
  end

  def reduce!
    loop do
      tmp = explodees

      if tmp.any?
        tmp.first.explode!

        next
      end

      tmp = splitees

      if tmp.any?
        tmp.first.split!

        next
      end

      break
    end
  end

  def magnitude
    if value.nil?
      3 * left.magnitude + 2 * right.magnitude
    else
      value
    end
  end

  def +(other)
    node = Pair.new([self.to_a, other.to_a], parent)

    node.reduce!

    node
  end

  def to_a
    tmp = []

    unless left.nil?
      if left.value.nil?
        tmp << left.to_a
      else
        tmp << left.value
      end
    end

    unless right.nil?
      if right.value.nil?
        tmp << right.to_a
      else
        tmp << right.value
      end
    end

    tmp.empty? ? value : tmp
  end

  def eql?(other)
    parent == other.parent && to_a == other.to_a
  end

  def to_s
    to_a.to_s
  end
end

