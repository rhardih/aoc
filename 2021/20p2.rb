=begin

--- Part Two ---

You still can't quite make out the details in the image. Maybe you just didn't
enhance it enough.

If you enhance the starting input image in the above example a total of 50
times, 3351 pixels are lit in the final output image.

Start again with the original input image and apply the image enhancement
algorithm 50 times. How many pixels are lit in the resulting image?

=end

require 'matrix'

require_relative "20"

algorithm, input_image_string = STDIN.read.split("\n\n")
input_image = Matrix.rows(input_image_string.split("\n").map(&:chars))

output_image = enhance(input_image, algorithm, 50)

puts "Number of lit pixels in the resulting image: #{output_image.count("#")}"
