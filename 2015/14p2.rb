=begin

--- Part Two ---

Seeing how reindeer move in bursts, Santa decides he's not pleased with the old
scoring system.

Instead, at the end of each second, he awards one point to the reindeer
currently in the lead. (If there are multiple reindeer tied for the lead, they
each get one point.) He keeps the traditional 2503 second time limit, of
course, as doing otherwise would be entirely ridiculous.

Given the example reindeer from above, after the first second, Dancer is in the
lead and gets one point. He stays in the lead until several seconds into
Comet's second burst: after the 140th second, Comet pulls into the lead and
gets his first point. Of course, since Dancer had been in the lead for the 139
seconds before that, he has accumulated 139 points by the 140th second.

After the 1000th second, Dancer has accumulated 689 points, while poor Comet,
our old champion, only has 312. So, with the new scoring system, Dancer would
win (if the race ended at 1000 seconds).

Again given the descriptions of each reindeer (in your puzzle input), after
exactly 2503 seconds, how many points does the winning reindeer have?

=end

Reindeer = Struct.new(
  :name,
  :speed,
  :fly_duration,
  :rest_duration,
  :distance,
  :resting,
  :countdown,
  :points,
)

reindeer = STDIN.readlines.map(&:split).map do |name, _, _, speed, _, _, fly_duration, _, _, _, _, _, _, rest_duration|
  speed = speed.to_i
  fly_duration = fly_duration.to_i
  rest_duration = rest_duration.to_i

  Reindeer.new(
    name,
    speed,
    fly_duration,
    rest_duration,
    0,
    false,
    fly_duration,
    0
  )
end

2503.times do |i|
  s = i + 1

  reindeer.each do |r|
    unless r.resting
      r.distance += r.speed
    end

    r.countdown -= 1

    if r.countdown == 0
      r.countdown = r.resting ? r.fly_duration : r.rest_duration
      r.resting = !r.resting
    end
  end

  max_distance = reindeer.max_by(&:distance).distance
  leaders = reindeer.select { |r| r.distance == max_distance }
  leaders.each { |r| r.points += 1 }
end

winner = reindeer.max_by(&:points)

puts "The winning reindeer was #{winner.name}. It has #{winner.points} points"

