=begin

--- Part Two ---

Now, you're ready to check the image for sea monsters.

The borders of each tile are not part of the actual image; start by removing
them.

In the example above, the tiles become:

.#.#..#. ##...#.# #..#####
###....# .#....#. .#......
##.##.## #.#.#..# #####...
###.#### #...#.## ###.#..#
##.#.... #.##.### #...#.##
...##### ###.#... .#####.#
....#..# ...##..# .#.###..
.####... #..#.... .#......

#..#.##. .#..###. #.##....
#.####.. #.####.# .#.###..
###.#.#. ..#.#### ##.#..##
#.####.. ..##..## ######.#
##..##.# ...#...# .#.#.#..
...#..#. .#.#.##. .###.###
.#.#.... #.##.#.. .###.##.
###.#... #..#.##. ######..

.#.#.### .##.##.# ..#.##..
.####.## #.#...## #.#..#.#
..#.#..# ..#.#.#. ####.###
#..####. ..#.#.#. ###.###.
#####..# ####...# ##....##
#.##..#. .#...#.. ####...#
.#.###.. ##..##.. ####.##.
...###.. .##...#. ..#..###

Remove the gaps to form the actual image:

.#.#..#.##...#.##..#####
###....#.#....#..#......
##.##.###.#.#..######...
###.#####...#.#####.#..#
##.#....#.##.####...#.##
...########.#....#####.#
....#..#...##..#.#.###..
.####...#..#.....#......
#..#.##..#..###.#.##....
#.####..#.####.#.#.###..
###.#.#...#.######.#..##
#.####....##..########.#
##..##.#...#...#.#.#.#..
...#..#..#.#.##..###.###
.#.#....#.##.#...###.##.
###.#...#..#.##.######..
.#.#.###.##.##.#..#.##..
.####.###.#...###.#..#.#
..#.#..#..#.#.#.####.###
#..####...#.#.#.###.###.
#####..#####...###....##
#.##..#..#...#..####...#
.#.###..##..##..####.##.
...###...##...#...#..###

Now, you're ready to search for sea monsters! Because your image is monochrome,
a sea monster will look like this:

                  # 
#    ##    ##    ###
 #  #  #  #  #  #   

When looking for this pattern in the image, the spaces can be anything; only the
# need to match. Also, you might need to rotate or flip your image before it's
oriented correctly to find sea monsters. In the above image, after flipping and
rotating it to the appropriate orientation, there are two sea monsters (marked
with O):

.####...#####..#...###..
#####..#..#.#.####..#.#.
.#.#...#.###...#.##.O#..
#.O.##.OO#.#.OO.##.OOO##
..#O.#O#.O##O..O.#O##.##
...#.#..##.##...#..#..##
#.##.#..#.#..#..##.#.#..
.###.##.....#...###.#...
#.####.#.#....##.#..#.#.
##...#..#....#..#...####
..#.##...###..#.#####..#
....#.##.#.#####....#...
..##.##.###.....#.##..#.
#...#...###..####....##.
.#.##...#.##.#.#.###...#
#.###.#..####...##..#...
#.###...#.##...#.##O###.
.O##.#OO.###OO##..OOO##.
..O#.O..O..O.#O##O##.###
#.#..##.########..#..##.
#.#####..#.#...##..#....
#....##..#.#########..##
#...#.....#..##...###.##
#..###....##.#...##.##.#
#
Determine how rough the waters are in the sea monsters' habitat by counting the
number of # that are not part of a sea monster. In the above example, the
habitat's water roughness is 273.

How many # are not part of a sea monster?

=end

require "matrix"

class Tile
  attr_accessor :id, :data

  def initialize(id_line = nil, image = nil)
    @id = id_line.scan(/\d+/).first.to_i unless id_line.nil?
    @data = Matrix[*image.map { |line| line.split("") }] unless image.nil?
  end

  def flipx
    Tile.new.tap do |t|
      rows = data.row_vectors.map(&:to_a).map(&:reverse)
      t.data = Matrix.rows(rows)
      t.id = id
    end
  end

  def flipy
    Tile.new.tap do |t|
      t.data = Matrix.rows(data.row_vectors.reverse)
      t.id = id
    end
  end

  def rotate
    flipy.tap do |t|
      t.data = t.data.transpose
    end
  end

  def variants
    @variants ||= [].tap do |v|
      [self, flipx, flipy].each do |t|
        v << t
        v << t.rotate
        v << t.rotate.rotate
        v << t.rotate.rotate.rotate
      end
    end.uniq
  end

  def fits_above?(other)
    id != other.id && data.row(-1) == other.data.row(0)
  end

  def fits_right_of?(other)
    id != other.id && data.column(0) == other.data.column(-1)
  end

  def fits_below?(other)
    id != other.id && data.row(0) == other.data.row(-1)
  end

  def fits_left_of?(other)
    id != other.id && data.column(-1) == other.data.column(0)
  end

  def ==(other)
    data == other.data
  end

  def eql?(other)
    data == other.data
  end

  def hash
    data.hash
  end

  def to_s
    rows = data.row_vectors.map { |rv| rv.to_a.join }
    "Tile id=#{id}\n#{rows.join("\n")}"
  end
end

class TileGrid
  attr_accessor :data

  def initialize(data)
    @data = data
  end

  def to_s
    groups = []

    @data.row_vectors.map do |tile_row|
      lines_by_index = Hash.new { |h,k| h[k] = Array.new }

      tile_row.each do |tile|
        tile.data.row_vectors.each_with_index do |trv, i|
          lines_by_index[i] << trv.to_a.join
        end
      end

      groups << lines_by_index.map { |_,v| v.join(" ") }
    end

    groups.map { |g| g.join("\n") }.join("\n\n")
  end
end

class Image
  attr_accessor :data
  attr_accessor :monster_spotted

  def initialize(grid = nil)
    return if grid.nil?

    tile_rows = []

    (0...grid.data.column_count).each do |y|
      lines_by_index = Hash.new { |h,k| h[k] = "" }

      (0...grid.data.row_count).each do |x|
        borderless_tile_data = grid.data[y,x].data.minor(1..-2, 1..-2)

        borderless_tile_data.row_vectors.each_with_index do |rv, i|
          lines_by_index[i] << rv.to_a.join
        end
      end

      tile_rows << lines_by_index.values
    end

    @data = Matrix.rows(tile_rows.flatten.map { |row| row.split("") })
    @monster_spotted = false
  end

  def flipx
    Image.new.tap do |image|
      rows = data.row_vectors.map(&:to_a).map(&:reverse)
      image.data = Matrix.rows(rows)
    end
  end

  def flipy
    Image.new.tap do |image|
      image.data = Matrix.rows(data.row_vectors.reverse)
    end
  end

  def rotate
    flipy.tap do |image|
      image.data = image.data.transpose
    end
  end

  def variants
    @variants ||= [].tap do |v|
      [self, flipx, flipy].each do |image|
        v << image
        v << image.rotate
        v << image.rotate.rotate
        v << image.rotate.rotate.rotate
      end
    end.uniq
  end

  def sea_monster
    @sea_monster ||= Matrix.rows([
      "                  # ",
      "#    ##    ##    ###",
      " #  #  #  #  #  #   ", 
    ].map { |line| line.split("") })
  end

  def sea_monster_body_size
    @sea_monster_body_size ||= lambda do
      sea_monster_body_size = 0

      (0...sea_monster.row_count).each do |y|
        (0...sea_monster.column_count).each do |x|
          sea_monster_body_size += 1 if sea_monster[y,x] == "#"
        end
      end

      sea_monster_body_size
    end.call
  end

  def has_sea_monster?
    with_sea_monsters.monster_spotted
  end

  def with_sea_monsters
    image = self.clone

    (0..@data.row_count - sea_monster.row_count).each do |y|
      (0..@data.column_count - sea_monster.column_count).each do |x|
        cutout = @data.minor(
          y, sea_monster.row_count,
          x, sea_monster.column_count)

        matches = 0
        (0...sea_monster.row_count).each do |smy|
          (0...sea_monster.column_count).each do |smx|
            if sea_monster[smy,smx] == cutout[smy,smx]
              matches += 1
            end
          end
        end

        if matches == sea_monster_body_size
          image.monster_spotted = true

          (0...sea_monster.row_count).each do |smy|
            (0...sea_monster.column_count).each do |smx|
              if sea_monster[smy,smx] == "#"
                image.data[y + smy, x + smx] = "O"
              end
            end
          end
        end
      end
    end

    image
  end

  def water_roughness
    value = 0

    (0..@data.row_count).each do |y|
      (0..@data.column_count).each do |x|
        value += 1 if @data[y,x] == "#"
      end
    end

    value
  end

  def eql?(other)
    @data == other.data
  end

  def hash
    @data.hash
  end

  def to_s
    @data.row_vectors.map { |rv| rv.to_a.join }.join("\n")
  end
end


tile_groups = STDIN.read.split("\n\n")
tiles = []

tile_groups.each do |tg|
  id_line, *image = tg.split("\n")

  tiles << Tile.new(id_line, image)
end

dimension = Math.sqrt(tiles.size).to_i
data = Matrix.build(dimension, dimension) { nil }
grid = TileGrid.new(data)

variants = tiles.map(&:variants).flatten

# Find candidate tiles for top left corner, stated as any tile where there is no
# other tile that fits above or left of.
#
# There should be *exactly* eight candidates. Four unique tiles by ID in a
# normal orientation and transposed one. Why eight? Imagine this tile:
#
#  #.
#  ##
#
# When transposed, the left border becomes the top and vice versa:
#
#  ##
#  .#
#
# So the requirement of no other tile left of or above is equivalent to before
# the transposition.
top_left_candidates = variants.find_all do |t0|
  !variants.any? { |t1| t1.fits_above?(t0) || t1.fits_left_of?(t0) }
end

# We could pick *any* of the eight resultant corner tiles and use it as our
# top-left basis, since after assembly, by flipping and/or rotating the final
# image, any of those eight corners could be positioned top left.
#
# This choice leads to matching the example, when printing out the assembled
# image.
grid.data[0,0] = top_left_candidates[1]

variants.reject! { |v| v.id == grid.data[0,0].id }

(0...dimension).each do |y|
  (0...dimension).each do |x|
    next if x == 0 && y == 0

    tile = nil

    if x > 0 && y > 0
      left = grid.data[y, x - 1]
      above = grid.data[y - 1, x]

      tile = variants.find do |tile|
        tile.fits_right_of?(left) &&
          tile.fits_below?(above)
      end
    elsif x > 0
      left = grid.data[y, x - 1]

      tile = variants.find { |tile| tile.fits_right_of?(left) }
    elsif y > 0
      above = grid.data[y - 1, x]

      tile = variants.find { |tile| tile.fits_below?(above) }
    end

    variants.reject! { |v| v.id == tile.id }
    grid.data[y,x] = tile
  end
end

image = Image.new(grid)

final_image = image.variants.find(&:has_sea_monster?)
# puts final_image

puts "Number of # that are not part of a sea monster: #{
  final_image.water_roughness
}"

