class Grid < Array
  attr_reader :width
  attr_reader :height
  attr_reader :locations
  attr_reader :flashed
  attr_reader :flashes

  def initialize(*args)
    super

    @height = @width = self.size
    @flashed = Array.new(width) { Array.new(height, false) }
    @flashes = 0
  end

  def generate_locations
    (0...width).to_a.product((0...height).to_a)
  end

  def locations
    @locations || generate_locations
  end

  def reset_flashed
    @flashed = Array.new(width) { Array.new(height, false) }
  end

  def flash(lx, ly)
    return if flashed[lx][ly]

    @flashes += 1

    offsets = [
      [-1, -1], [0, -1], [1, -1],
      [-1, 0], [1, 0],
      [-1, 1], [0, 1], [1, 1]
    ]

    offsets.each do |x_offset, y_offset|
      x, y = [lx + x_offset, ly + y_offset]

      next if x < 0 || x >= width
      next if y < 0 || y >= height

      self[x][y] += 1 unless flashed[x][y]
    end

    flashed[lx][ly] = true
    self[lx][ly] = 0
  end

  def step
    reset_flashed

    locations.each { |x, y| self[x][y] += 1 }

    until locations.none? { |x, y| self[x][y] > 9 }
      locations.each do |x, y|
        flash(x, y) if self[x][y] > 9
      end
    end
  end

  def to_s
    self.map.with_index do |row, x|
      row.map.with_index do |value, y|
        if flashed[x][y]
          "\033[34m#{self[x][y]}\033[0m"
        else
          self[x][y]
        end
      end.join
    end.join("\n")
  end
end

