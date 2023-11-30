=begin

--- Day 14: Reindeer Olympics ---

This year is the Reindeer Olympics! Reindeer can fly at high speeds, but must
rest occasionally to recover their energy. Santa would like to know which of
his reindeer is fastest, and so he has them race.

Reindeer can only either be flying (always at their top speed) or resting (not
moving at all), and always spend whole seconds in either state.

For example, suppose you have the following Reindeer:

- Comet can fly 14 km/s for 10 seconds, but then must rest for 127 seconds.
- Dancer can fly 16 km/s for 11 seconds, but then must rest for 162 seconds.

After one second, Comet has gone 14 km, while Dancer has gone 16 km. After ten
seconds, Comet has gone 140 km, while Dancer has gone 160 km. On the eleventh
second, Comet begins resting (staying at 140 km), and Dancer continues on for a
total distance of 176 km. On the 12th second, both reindeer are resting. They
continue to rest until the 138th second, when Comet flies for another ten
seconds. On the 174th second, Dancer flies for another 11 seconds.

In this example, after the 1000th second, both reindeer are resting, and Comet
is in the lead at 1120 km (poor Dancer has only gotten 1056 km by that point).
So, in this situation, Comet would win (if the race ended at 1000 seconds).

Given the descriptions of each reindeer (in your puzzle input), after exactly
2503 seconds, what distance has the winning reindeer traveled?

=end

Reindeer = Struct.new(
  :name,
  :speed,
  :fly_duration,
  :rest_duration,
  :distance,
  :resting,
  :countdown,
)

reindeer = STDIN.readlines.map(&:split).map do |name, _, _, speed, _, _, fly_duration, _, _, _, _, _, _, rest_duration|
  speed = speed.to_i
  fly_duration = fly_duration.to_i
  rest_duration = rest_duration.to_i

  Reindeer.new(name, speed, fly_duration, rest_duration, 0, false, fly_duration)
end

2503.times do |i|
  s = i + 1

  reindeer.each do |r|
    unless r.resting
      r.distance += r.speed
    end

    # puts "#{s}: #{r.name}: #{r.distance}" if s == 1
    # puts "#{s}: #{r.name}: #{r.distance}" if s == 10
    # puts "#{s}: #{r.name}: #{r.distance}" if s == 11
    # puts "#{s}: #{r.name}: #{r.distance}" if s == 12
    # puts "#{s}: #{r.name}: #{r.distance}" if s == 138
    # puts "#{s}: #{r.name}: #{r.distance}" if s == 148
    # puts "#{s}: #{r.name}: #{r.distance}" if s == 174

    r.countdown -= 1

    if r.countdown == 0
      r.countdown = r.resting ? r.fly_duration : r.rest_duration
      r.resting = !r.resting
    end
  end
end

winner = reindeer.max_by(&:distance)

puts "The winning reindeer was #{winner.name}. It traveled #{winner.distance}km"

