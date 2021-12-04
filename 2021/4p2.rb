=begin

--- Part Two ---

On the other hand, it might be wise to try a different strategy: let the giant
squid win.

You aren't sure how many bingo boards a giant squid could play at once, so
rather than waste time counting its arms, the safe thing to do is to figure out
which board will win last and choose that one. That way, no matter which boards
it picks, it will win for sure.

In the above example, the second board is the last to win, which happens after
13 is eventually called and its middle column is completely marked. If you were
to keep playing until this point, the second board would have a sum of unmarked
numbers equal to 148 for a final score of 148 * 13 = 1924.

Figure out which board will win last. Once it wins, what would its final score
be?

=end

require "matrix"

class Number
  attr_reader :value
  attr_accessor :marked

  def initialize(value)
    @value = value
    @marked = false
  end

  def to_s
    "#{value}:#{marked}"
  end
end

class Board < Matrix
  attr_accessor :won

  def initialize(*args)
    super(*args)

    @won = false
  end
end

numbers_string, *boards_string = STDIN.read.split("\n\n")
numbers = numbers_string.split(",").map(&:to_i)
boards = boards_string.map do |board_string|
  board_arr = board_string.split("\n").map do |row_string|
    row_string.split(" ").map do |number_string|
      Number.new(number_string.to_i)
    end
  end

  Board.rows(board_arr)
end

def mark(boards, value)
  last_winning_board = nil

  boards.each do |board|
    next if board.won

    board.each do |number|
      number.marked = true if number.value == value
    end

    # Check by row
    (0...board.column_size).each do |row_index|
      row = board.row(row_index)
      board.won = true if row.all?(&:marked)
    end

    # Check by column
    (0...board.row_size).each do |column_index|
      column = board.column(column_index)
      board.won = true if column.all?(&:marked)
    end

    last_winning_board = board if board.won
  end

  last_winning_board
end

numbers.each do |n|
  last_winning_board = mark(boards, n)

  if boards.all?(&:won)
    sum_of_unmarked = last_winning_board.reduce(0) do |sum, number|
      number.marked ? sum : sum + number.value
    end

    puts "Final score of last board to win: #{sum_of_unmarked * n}"

    break
  end
end
