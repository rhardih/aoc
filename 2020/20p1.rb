=begin

--- Day 20: Jurassic Jigsaw ---

The high-speed train leaves the forest and quickly carries you south. You can
even see a desert in the distance! Since you have some spare time, you might as
well see if there was anything interesting in the image the Mythical
Information Bureau satellite captured.

After decoding the satellite messages, you discover that the data actually
contains many small images created by the satellite's camera array. The camera
array consists of many cameras; rather than produce a single square image, they
produce many smaller square image tiles that need to be reassembled back into a
single image.

Each camera in the camera array returns a single monochrome image tile with a
random unique ID number. The tiles (your puzzle input) arrived in a random
order.

Worse yet, the camera array appears to be malfunctioning: each image tile has
been rotated and flipped to a random orientation. Your first task is to
reassemble the original image by orienting the tiles so they fit together.

To show how the tiles should be reassembled, each tile's image data includes a
border that should line up exactly with its adjacent tiles. All tiles have this
border, and the border lines up exactly when the tiles are both oriented
correctly. Tiles at the edge of the image also have this border, but the
outermost edges won't line up with any other tiles.

For example, suppose you have the following nine tiles:

Tile 2311:
..##.#..#.
##..#.....
#...##..#.
####.#...#
##.##.###.
##...#.###
.#.#.#..##
..#....#..
###...#.#.
..###..###

Tile 1951:
#.##...##.
#.####...#
.....#..##
#...######
.##.#....#
.###.#####
###.##.##.
.###....#.
..#.#..#.#
#...##.#..

Tile 1171:
####...##.
#..##.#..#
##.#..#.#.
.###.####.
..###.####
.##....##.
.#...####.
#.##.####.
####..#...
.....##...

Tile 1427:
###.##.#..
.#..#.##..
.#.##.#..#
#.#.#.##.#
....#...##
...##..##.
...#.#####
.#.####.#.
..#..###.#
..##.#..#.

Tile 1489:
##.#.#....
..##...#..
.##..##...
..#...#...
#####...#.
#..#.#.#.#
...#.#.#..
##.#...##.
..##.##.##
###.##.#..

Tile 2473:
#....####.
#..#.##...
#.##..#...
######.#.#
.#...#.#.#
.#########
.###.#..#.
########.#
##...##.#.
..###.#.#.

Tile 2971:
..#.#....#
#...###...
#.#.###...
##.##..#..
.#####..##
.#..####.#
#..#.#..#.
..####.###
..#.#.###.
...#.#.#.#

Tile 2729:
...#.#.#.#
####.#....
..#.#.....
....#..#.#
.##..##.#.
.#.####...
####.#.#..
##.####...
##..#.##..
#.##...##.

Tile 3079:
#.#.#####.
.#..######
..#.......
######....
####.#..#.
.#...#.##.
#.#####.##
..#.###...
..#.......
..#.###...

By rotating, flipping, and rearranging them, you can find a square arrangement
that causes all adjacent borders to line up:

#...##.#.. ..###..### #.#.#####.
..#.#..#.# ###...#.#. .#..######
.###....#. ..#....#.. ..#.......
###.##.##. .#.#.#..## ######....
.###.##### ##...#.### ####.#..#.
.##.#....# ##.##.###. .#...#.##.
#...###### ####.#...# #.#####.##
.....#..## #...##..#. ..#.###...
#.####...# ##..#..... ..#.......
#.##...##. ..##.#..#. ..#.###...

#.##...##. ..##.#..#. ..#.###...
##..#.##.. ..#..###.# ##.##....#
##.####... .#.####.#. ..#.###..#
####.#.#.. ...#.##### ###.#..###
.#.####... ...##..##. .######.##
.##..##.#. ....#...## #.#.#.#...
....#..#.# #.#.#.##.# #.###.###.
..#.#..... .#.##.#..# #.###.##..
####.#.... .#..#.##.. .######...
...#.#.#.# ###.##.#.. .##...####

...#.#.#.# ###.##.#.. .##...####
..#.#.###. ..##.##.## #..#.##..#
..####.### ##.#...##. .#.#..#.##
#..#.#..#. ...#.#.#.. .####.###.
.#..####.# #..#.#.#.# ####.###..
.#####..## #####...#. .##....##.
##.##..#.. ..#...#... .####...#.
#.#.###... .##..##... .####.##.#
#...###... ..##...#.. ...#..####
..#.#....# ##.#.#.... ...##.....

For reference, the IDs of the above tiles are:

1951    2311    3079
2729    1427    2473
2971    1489    1171

To check that you've assembled the image correctly, multiply the IDs of the
four corner tiles together. If you do this with the assembled tiles from the
example above, you get 1951 * 3079 * 2971 * 1171 = 20899048083289.

Assemble the tiles into an image. What do you get if you multiply together the
IDs of the four corner tiles?

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

tile_groups = STDIN.read.split("\n\n")
tiles = []

tile_groups.each do |tg|
  id_line, *image = tg.split("\n")

  tiles << Tile.new(id_line, image)
end

all_variants = tiles.map(&:variants).flatten

top_border = all_variants.find_all do |t0|
  !all_variants.any? do |t1|
    t1.fits_above?(t0)
  end
end

right_border = all_variants.find_all do |t0|
  !all_variants.any? do |t1|
    t1.fits_right_of?(t0)
  end
end

bottom_border = all_variants.find_all do |t0|
  !all_variants.any? do |t1|
    t1.fits_below?(t0)
  end
end

left_border = all_variants.find_all do |t0|
  !all_variants.any? do |t1|
    t1.fits_left_of?(t0)
  end
end

top_left = left_border & top_border
top_right = top_border & right_border
bottom_right = right_border & bottom_border
bottom_left = bottom_border & left_border

result = [
  top_left,
  top_right,
  bottom_right,
  bottom_left
].flatten.map(&:id).uniq.reduce(:*)

puts "Multiple of the IDs of the four corner tiles: #{result}"
