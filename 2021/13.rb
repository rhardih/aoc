require 'matrix'

class Paper < Matrix
  def to_s
    self.rows.map { |row| row.join }.join("\n")
  end

  def width
    column_count
  end

  def height
    row_count
  end
end

def handle_input
  coordinate_section, fold_instructions_section = STDIN.read.split("\n\n")

  coordinates = coordinate_section.split("\n").map do |line|
    line.split(",").map(&:to_i)
  end

  instructions = fold_instructions = fold_instructions_section.
    split("\n").reduce([]) do |memo, line|
      direction, location = line.scan(/fold along ([xy])=(\d+)/).flatten
      memo << [direction, location.to_i]
      memo
    end

  x_max = coordinates.max { |a, b| a.first <=> b.first }.first
  y_max = coordinates.max { |a, b| a.last <=> b.last }.last
  dim = [x_max, y_max].max + 1

  paper = coordinates.reduce(Paper.build(dim) { "." }) do |memo, coordinate|
    x, y = coordinate
    memo[y, x] = "#"
    memo
  end

  [paper, instructions]
end

def fold(paper, fold_instructions, one_fold = true)
  fold_instructions.each do |direction, location|
    if direction == 'y'
      (0...location).each do |y|
        (0...paper.width).each do |x|
          y_fold = location - y + location

          if paper[y_fold, x] == "#"
            paper[y, x] = "#"
            paper[y_fold, x] = "."
          end
        end
      end
    else
      (0...paper.height).each do |y|
        (0...location).each do |x|
          x_fold = location - x + location

          if paper[y, x_fold] == "#"
            paper[y, x] = "#"
            paper[y, x_fold] = "."
          end
        end
      end
    end

    break if one_fold
  end
end

