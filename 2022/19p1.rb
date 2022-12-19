=begin

--- Day 19: Not Enough Minerals ---

Your scans show that the lava did indeed form obsidian!

The wind has changed direction enough to stop sending lava droplets toward you,
so you and the elephants exit the cave. As you do, you notice a collection of
geodes around the pond. Perhaps you could use the obsidian to create some
geode-cracking robots and break them open?

To collect the obsidian from the bottom of the pond, you'll need waterproof
obsidian-collecting robots. Fortunately, there is an abundant amount of clay
nearby that you can use to make them waterproof.

In order to harvest the clay, you'll need special-purpose clay-collecting
robots. To make any type of robot, you'll need ore, which is also plentiful but
in the opposite direction from the clay.

Collecting ore requires ore-collecting robots with big drills. Fortunately, you
have exactly one ore-collecting robot in your pack that you can use to kickstart
the whole operation.

Each robot can collect 1 of its resource type per minute. It also takes one
minute for the robot factory (also conveniently from your pack) to construct any
type of robot, although it consumes the necessary resources available when
construction begins.

The robot factory has many blueprints (your puzzle input) you can choose from,
but once you've configured it with a blueprint, you can't change it. You'll need
to work out which blueprint is best.

For example:

Blueprint 1:
  Each ore robot costs 4 ore.
  Each clay robot costs 2 ore.
  Each obsidian robot costs 3 ore and 14 clay.
  Each geode robot costs 2 ore and 7 obsidian.

Blueprint 2:
  Each ore robot costs 2 ore.
  Each clay robot costs 3 ore.
  Each obsidian robot costs 3 ore and 8 clay.
  Each geode robot costs 3 ore and 12 obsidian.

(Blueprints have been line-wrapped here for legibility. The robot factory's
actual assortment of blueprints are provided one blueprint per line.)

The elephants are starting to look hungry, so you shouldn't take too long; you
need to figure out which blueprint would maximize the number of opened geodes
after 24 minutes by figuring out which robots to build and when to build them.

Using blueprint 1 in the example above, the largest number of geodes you could
open in 24 minutes is 9. One way to achieve that is:

== Minute 1 ==
1 ore-collecting robot collects 1 ore; you now have 1 ore.

== Minute 2 ==
1 ore-collecting robot collects 1 ore; you now have 2 ore.

== Minute 3 ==
Spend 2 ore to start building a clay-collecting robot.
1 ore-collecting robot collects 1 ore; you now have 1 ore.
The new clay-collecting robot is ready; you now have 1 of them.

== Minute 4 ==
1 ore-collecting robot collects 1 ore; you now have 2 ore.
1 clay-collecting robot collects 1 clay; you now have 1 clay.

== Minute 5 ==
Spend 2 ore to start building a clay-collecting robot.
1 ore-collecting robot collects 1 ore; you now have 1 ore.
1 clay-collecting robot collects 1 clay; you now have 2 clay.
The new clay-collecting robot is ready; you now have 2 of them.

== Minute 6 ==
1 ore-collecting robot collects 1 ore; you now have 2 ore.
2 clay-collecting robots collect 2 clay; you now have 4 clay.

== Minute 7 ==
Spend 2 ore to start building a clay-collecting robot.
1 ore-collecting robot collects 1 ore; you now have 1 ore.
2 clay-collecting robots collect 2 clay; you now have 6 clay.
The new clay-collecting robot is ready; you now have 3 of them.

== Minute 8 ==
1 ore-collecting robot collects 1 ore; you now have 2 ore.
3 clay-collecting robots collect 3 clay; you now have 9 clay.

== Minute 9 ==
1 ore-collecting robot collects 1 ore; you now have 3 ore.
3 clay-collecting robots collect 3 clay; you now have 12 clay.

== Minute 10 ==
1 ore-collecting robot collects 1 ore; you now have 4 ore.
3 clay-collecting robots collect 3 clay; you now have 15 clay.

== Minute 11 ==
Spend 3 ore and 14 clay to start building an obsidian-collecting robot.
1 ore-collecting robot collects 1 ore; you now have 2 ore.
3 clay-collecting robots collect 3 clay; you now have 4 clay.
The new obsidian-collecting robot is ready; you now have 1 of them.

== Minute 12 ==
Spend 2 ore to start building a clay-collecting robot.
1 ore-collecting robot collects 1 ore; you now have 1 ore.
3 clay-collecting robots collect 3 clay; you now have 7 clay.
1 obsidian-collecting robot collects 1 obsidian; you now have 1 obsidian.
The new clay-collecting robot is ready; you now have 4 of them.

== Minute 13 ==
1 ore-collecting robot collects 1 ore; you now have 2 ore.
4 clay-collecting robots collect 4 clay; you now have 11 clay.
1 obsidian-collecting robot collects 1 obsidian; you now have 2 obsidian.

== Minute 14 ==
1 ore-collecting robot collects 1 ore; you now have 3 ore.
4 clay-collecting robots collect 4 clay; you now have 15 clay.
1 obsidian-collecting robot collects 1 obsidian; you now have 3 obsidian.

== Minute 15 ==
Spend 3 ore and 14 clay to start building an obsidian-collecting robot.
1 ore-collecting robot collects 1 ore; you now have 1 ore.
4 clay-collecting robots collect 4 clay; you now have 5 clay.
1 obsidian-collecting robot collects 1 obsidian; you now have 4 obsidian.
The new obsidian-collecting robot is ready; you now have 2 of them.

== Minute 16 ==
1 ore-collecting robot collects 1 ore; you now have 2 ore.
4 clay-collecting robots collect 4 clay; you now have 9 clay.
2 obsidian-collecting robots collect 2 obsidian; you now have 6 obsidian.

== Minute 17 ==
1 ore-collecting robot collects 1 ore; you now have 3 ore.
4 clay-collecting robots collect 4 clay; you now have 13 clay.
2 obsidian-collecting robots collect 2 obsidian; you now have 8 obsidian.

== Minute 18 ==
Spend 2 ore and 7 obsidian to start building a geode-cracking robot.
1 ore-collecting robot collects 1 ore; you now have 2 ore.
4 clay-collecting robots collect 4 clay; you now have 17 clay.
2 obsidian-collecting robots collect 2 obsidian; you now have 3 obsidian.
The new geode-cracking robot is ready; you now have 1 of them.

== Minute 19 ==
1 ore-collecting robot collects 1 ore; you now have 3 ore.
4 clay-collecting robots collect 4 clay; you now have 21 clay.
2 obsidian-collecting robots collect 2 obsidian; you now have 5 obsidian.
1 geode-cracking robot cracks 1 geode; you now have 1 open geode.

== Minute 20 ==
1 ore-collecting robot collects 1 ore; you now have 4 ore.
4 clay-collecting robots collect 4 clay; you now have 25 clay.
2 obsidian-collecting robots collect 2 obsidian; you now have 7 obsidian.
1 geode-cracking robot cracks 1 geode; you now have 2 open geodes.

== Minute 21 ==
Spend 2 ore and 7 obsidian to start building a geode-cracking robot.
1 ore-collecting robot collects 1 ore; you now have 3 ore.
4 clay-collecting robots collect 4 clay; you now have 29 clay.
2 obsidian-collecting robots collect 2 obsidian; you now have 2 obsidian.
1 geode-cracking robot cracks 1 geode; you now have 3 open geodes.
The new geode-cracking robot is ready; you now have 2 of them.

== Minute 22 ==
1 ore-collecting robot collects 1 ore; you now have 4 ore.
4 clay-collecting robots collect 4 clay; you now have 33 clay.
2 obsidian-collecting robots collect 2 obsidian; you now have 4 obsidian.
2 geode-cracking robots crack 2 geodes; you now have 5 open geodes.

== Minute 23 ==
1 ore-collecting robot collects 1 ore; you now have 5 ore.
4 clay-collecting robots collect 4 clay; you now have 37 clay.
2 obsidian-collecting robots collect 2 obsidian; you now have 6 obsidian.
2 geode-cracking robots crack 2 geodes; you now have 7 open geodes.

== Minute 24 ==
1 ore-collecting robot collects 1 ore; you now have 6 ore.
4 clay-collecting robots collect 4 clay; you now have 41 clay.
2 obsidian-collecting robots collect 2 obsidian; you now have 8 obsidian.
2 geode-cracking robots crack 2 geodes; you now have 9 open geodes.

However, by using blueprint 2 in the example above, you could do even better:
the largest number of geodes you could open in 24 minutes is 12.

Determine the quality level of each blueprint by multiplying that blueprint's ID
number with the largest number of geodes that can be opened in 24 minutes using
that blueprint. In this example, the first blueprint has ID 1 and can open 9
geodes, so its quality level is 9. The second blueprint has ID 2 and can open 12
geodes, so its quality level is 24. Finally, if you add up the quality levels of
all of the blueprints in the list, you get 33.

Determine the quality level of each blueprint using the largest number of geodes
it could produce in 24 minutes. What do you get if you add up the quality level
of all of the blueprints in your list?

=end

DEBUG = true

def debug(s)
  puts s if DEBUG
end

Cost = Struct.new(:ore, :clay, :obsidian, :geode)
Blueprint = Struct.new(
  :id,
  :ore_robot_cost,
  :clay_robot_cost,
  :obsidian_robot_cost,
  :geode_robot_cost
)

blueprints = []

STDIN.read.split("\n").each do |line|
  id, c0, c1, c2, c3, c4, c5 = line.scan(/\d+/).map(&:to_i)

  blueprints << Blueprint.new(
    id,
    Cost.new(c0, 0, 0, 0),
    Cost.new(c1, 0, 0, 0),
    Cost.new(c2, c3, 0, 0),
    Cost.new(c4, 0, c5, 0)
  )

  # break
end

quality_levels = blueprints.map do |blueprint|
  pp blueprint

  max = 0

  for geode_wait in 0...12 do
    for obsidian_wait in 0...12 do
      # Start out with one ore collecting robot
      robots = { ore: 1, clay: 0, obsidian: 0, geode: 0 }
      resources = { ore: 0, clay: 0, obsidian: 0, geode: 0 }

      for minute in 1..24 do
        puts
        debug "== Minute #{minute} =="

        build_geode_robot =
          resources[:ore] >= blueprint.geode_robot_cost.ore &&
          resources[:obsidian] >= blueprint.geode_robot_cost.obsidian

        # Don't spend on a clay robot, if we're close to being able to build a
        # geode robot
        save_for_geode_robot = blueprint.geode_robot_cost.obsidian <=
          resources[:obsidian] + geode_wait * robots[:obsidian]
        can_afford_obsidian_robot = 
          resources[:ore] >= blueprint.obsidian_robot_cost.ore &&
          resources[:clay] >= blueprint.obsidian_robot_cost.clay
        build_obsidian_robot = !save_for_geode_robot && can_afford_obsidian_robot

        # Don't spend on a clay robot, if we're close to being able to build an
        # obsidian robot
        save_for_obsidian_robot = blueprint.obsidian_robot_cost.clay <=
          resources[:clay] + obsidian_wait * robots[:clay]
        can_afford_clay_robot = resources[:ore] >= blueprint.clay_robot_cost.ore
        build_clay_robot = !save_for_obsidian_robot && can_afford_clay_robot

        # ore_in_two_minutes = resources[:ore] + obsidian_wait * robots[:ore]
        can_afford_ore_robot = resources[:ore] >= blueprint.ore_robot_cost.ore
        build_ore_robot = 
          # blueprint.obsidian_robot_cost.ore > ore_in_two_minutes &&
          can_afford_ore_robot

        if build_geode_robot
          debug "Spend #{blueprint.geode_robot_cost.ore} ore and #{blueprint.geode_robot_cost.obsidian} obsidian to start building a geode-cracking robot."
          resources[:ore] -= blueprint.geode_robot_cost.ore
          resources[:obsidian] -= blueprint.geode_robot_cost.obsidian
        elsif build_obsidian_robot
          debug "Spend #{blueprint.obsidian_robot_cost.ore} ore and #{blueprint.obsidian_robot_cost.clay} clay to start building an obsidian-collecting robot."
          resources[:ore] -= blueprint.obsidian_robot_cost.ore
          resources[:clay] -= blueprint.obsidian_robot_cost.clay
        elsif build_clay_robot
          debug "Spend #{blueprint.clay_robot_cost.ore} ore to start building a clay-collecting robot."
          resources[:ore] -= blueprint.clay_robot_cost.ore
        elsif build_ore_robot
          debug "Spend #{blueprint.ore_robot_cost.ore} ore to start building a ore-collecting robot."
          resources[:ore] -= blueprint.ore_robot_cost.ore
          # throw "should not build ore robot"
        end

        robots.each do |type, count|
          next if count == 0

          resources[type] += robots[type]

          if type == :geode && count > 0
            debug "#{robots[:geode]} geode-cracking robots crack #{robots[:geode]} geodes; you now have #{resources[:geode]} open geodes."
          else
            debug "#{robots[type]} #{type}-collecting robot collects #{robots[type]} #{type}; you now have #{resources[type]} #{type}."
          end
        end

        if build_geode_robot
          robots[:geode] += 1
          debug "The new geode-collecting robot is ready; you now have #{robots[:geode]} of them."
        elsif build_obsidian_robot
          robots[:obsidian] += 1
          debug "The new obsidian-collecting robot is ready; you now have #{robots[:obsidian]} of them."
        elsif build_clay_robot
          robots[:clay] += 1
          debug "The new clay-collecting robot is ready; you now have #{robots[:clay]} of them."
        elsif build_ore_robot
          robots[:ore] += 1
          debug "The new ore-collecting robot is ready; you now have #{robots[:ore]} of them."
        end
      end

      max = resources[:geode] if max < resources[:geode]
    end
  end

  puts max
  puts resources[:geode]

  # blueprint.id * resources[:geode]
  blueprint.id * max
end

p quality_levels

puts "Sum of quality levels of all of the blueprints: #{quality_levels.sum}"
