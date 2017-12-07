tower = {}

STDIN.read.split("\n").each do |l|
  name, weight, *rest = l.split(" ")

  tower[name] = {
    weight: weight.tr("()", ""),
    above: []
  }

  unless rest.empty?
    # leave out arrow
    rest[1..-1].each do |p|
      tower[name][:above] << p.tr(",", "")
    end
  end
end

# Find the only program no other holds
tower.each do |k, v|
  v[:above].each do |name|
    tower[name][:held] = true
  end
end

p tower.find { |k, v| !v.key?(:held) }
