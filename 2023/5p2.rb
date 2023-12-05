a_seeds, a_sts, a_stf, a_ftw, a_wtl, a_ltt, a_tth, a_htl = STDIN.read.split("\n\n")

# sts = Hash.new { |h,k| h[k] = k }
# stf = Hash.new { |h,k| h[k] = k }
# ftw = Hash.new { |h,k| h[k] = k }
# wtl = Hash.new { |h,k| h[k] = k }
# ltt = Hash.new { |h,k| h[k] = k }
# tth = Hash.new { |h,k| h[k] = k }
# htl = Hash.new { |h,k| h[k] = k }

sts, stf, ftw, wtl, ltt, tth, htl = [
  a_sts, 
  a_stf, 
  a_ftw, 
  a_wtl, 
  a_ltt, 
  a_tth, 
  a_htl, 
].map do |a|
  maps = a.scan(/\d+ \d+ \d+/).map do |element|
    element.split(" ").map(&:to_i)
  end

  Hash.new do |h, k|
    map = maps.find { |drs, srs, rl| k >= srs && k <= srs + rl }

    if map.nil?
      h[k] = k
    else
      drs, srs, rl = map

      h[k] = drs + (k - srs)
    end
  end
end

seeds = a_seeds.scan(/\d+/).map(&:to_i)

# seeds.each do |seed|
#   puts "Seed number #{seed} corresponds to soil number #{sts[seed]}."
# end

new_seeds = []

seeds.each_slice(2) do |start, length|
  length.times { |i| new_seeds << start + i }
end

lowest = new_seeds.map do |seed|
  htl[tth[ltt[wtl[ftw[stf[sts[seed]]]]]]]
end.min

puts lowest
