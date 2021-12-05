class Password
  attr_reader :value

  def initialize(value)
    @value = value
  end

  def next!
    last, *rev_head = @value.chars.reverse
    head = rev_head.reverse.join

    if last == 'z'
      @value = next_password(head) + 'a'
    else
      @value = head + (last.ord + 1).chr
    end

    @value
  end

  def valid?
    chars = @value.chars

    # Passwords must include one increasing straight of at least three letters
    return false if chars.each_cons(3).none? do |a, b, c|
      a.ord + 1 == b.ord && b.ord + 1 == c.ord
    end

    # Passwords may not contain the letters i, o, or l
    return false unless (chars & ['i', 'o', 'l']).empty?

    # Passwords must contain at least two different, non-overlapping pairs of
    # letters
    return false unless chars.chunk(&:itself).map do |_, sequence|
      sequence.length
    end.count(2) >= 2

    true
  end

  def to_s
    value
  end

	private

	def next_password(value)
		last, *rev_head = value.chars.reverse
		head = rev_head.reverse.join
		last == 'z' ? next_password(head) + 'a' : head + (last.ord + 1).chr
	end
end
