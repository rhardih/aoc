def enhance(input_image, algorithm, iteration)
  # The starting image extends infinitely in all directions, initially with dark
  # pixels
  fill = "."
  output_image = nil

  iteration.times do
    padded_input_image = Matrix.build(
      input_image.column_count + 4,
      input_image.row_count + 4
    ) { fill }

    # The fill might change according to the algorithm, e.g., a 9 pixel region,
    # that is all dark pixels:
    #
    # ...
    # ...
    # ...
    #
    # Would equal 00000000, and that might not be equal to the current pixel
    # value. Same would go for:
    #
    # ###
    # ###
    # ###
    #
    # 111111111
    fill = algorithm[(fill * 9).tr(".#", "01").to_i(2)]

    output_image = padded_input_image.dup

    padded_input_image[2...-2, 2...-2] = input_image

    padded_input_image.each_with_index do |_, row, col|
      if row == 0 || row == padded_input_image.row_count - 1 ||
          col == 0 || col == padded_input_image.column_count - 1
        output_image[row, col] = fill
      else
        neighbourhood = padded_input_image.minor(
          (row - 1)..(row + 1), (col - 1)..(col + 1)
        )

        index = neighbourhood.to_a.flatten.join.tr(".#", "01").to_i(2)

        output_image[row, col] = algorithm[index]
      end
    end

    input_image = output_image
  end

  output_image
end
