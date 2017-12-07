tower = {}

STDIN.read.split("\n").each do |l|
  name, weight, *rest = l.split(" ")

  tower[name] = {
    weight: weight.tr("()", "").to_i,
    above: []
  }

  unless rest.empty?
    # leave out arrow
    rest[1..-1].each do |p|
      tower[name][:above] << { name: p.tr(",", "") }
    end
  end
end

def sub_weight(t, n)
  t[n][:weight] +
    t[n][:above].inject(0) { |a, h| a + sub_weight(t, h[:name]) }
end

# Fill in weights
tower.each do |k, v|
  v[:above].each do |a|
    a[:weight] = sub_weight(tower, a[:name])
  end
end

tower.each do |k, v|
  ext_w = -> (h) { h[:weight] }
  ab = v[:above]
  found = nil
  delta = 0

  while ab.any?
    if ab.map(&ext_w).uniq.size > 1
      # Map weights and no. of occurences
      w_count = ab.each_with_object(Hash.new(0)) { |e, c| c[e[:weight]] += 1 }

      # How much is the difference?
      max = w_count.max_by { |k, v| k }.first
      min = w_count.min_by { |k, v| k }.first
      delta = max - min

      # The one that sticks out
      single_val = w_count.find { |k, v| v == 1 }.first
      tmp = ab.find { |e| e[:weight] == single_val }

      found = tmp[:name]
      ab = tower[found][:above]
    else
      break
    end
  end

  unless found.nil?
    w = tower[found][:weight]
    puts %Q{Program "#{found}" is not the correct weight. It weighs #{w}, but should weigh #{w - delta}.}
    break
  end
end
