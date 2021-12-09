class HeightMap < Array
  attr_reader :width
  attr_reader :height

  def initialize(*args)
    super

    @width = self[0].size
    @height = self.size
  end

  def locations
    (0...width).to_a.product((0...height).to_a)
  end
end
