image = Array.new(6 * 25)

STDIN.read.chomp.split("").each_slice(6 * 25).each do |layer|
  layer.each_index do |i|
    if image[i].nil? || image[i] == 2
      image[i] = " " if layer[i] == "0"
      image[i] = "#" if layer[i] == "1"
    end
  end
end

puts image.each_slice(25).map(&:join).join("\n")
