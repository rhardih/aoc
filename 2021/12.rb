class Cave
  attr_reader :name, :connected_caves

  def initialize(name)
    @name = name
    @connected_caves = []
  end

  def is_big?
    name.upcase == name
  end

  def is_start?
    name == "start"
  end

  def is_end?
    name == "end"
  end

  def to_s
    name
  end
end
