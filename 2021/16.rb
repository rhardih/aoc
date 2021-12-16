class Packet
  attr_reader :bin, :version, :type_id
  attr_reader :sub_packets

  def self.from_hex(hex)
    expansions = { 
      "0" => "0000", "1" => "0001", "2" => "0010", "3" => "0011",
      "4" => "0100", "5" => "0101", "6" => "0110", "7" => "0111",
      "8" => "1000", "9" => "1001", "A" => "1010", "B" => "1011",
      "C" => "1100", "D" => "1101", "E" => "1110", "F" => "1111"
    }

    Packet.new(hex.chars.map { |char| expansions[char] }.join)
  end

  def initialize(bin)
    @bin = bin
    @version = bin[0,3].to_i(2)
    @type_id = bin[3,3].to_i(2)
    @sub_packets = []

    # Initialize sub_packets as well
    if operator?
      if length_type_id == "0"
        index = 6 + 1 + 15

        # Can't make a packet of zeroes
        until bin[index..-1].chars.all?("0")
          next_packet = Packet.new(bin[index..-1])

          @sub_packets << next_packet

          index += next_packet.size
        end
      else
        index = 6 + 1 + 11

        no_sub_packets.times do
          break if bin[index..-1].chars.all?("0")

          next_packet = Packet.new(bin[index..-1])

          @sub_packets << next_packet

          index += next_packet.size
        end
      end
    end
  end

  def operator?
    type_id != 4
  end

  def length_type_id
    bin[6]
  end

  def length_sub_packets
    raise "length_sub_packets" if length_type_id != "0"

    bin[7,15].to_i(2)
  end

  def no_sub_packets
    raise "no_sub_packets" if length_type_id != "1"

    bin[7,11].to_i(2)
  end

  def header_size
    unless operator?
      6
    else
      6 + 1 + (length_type_id == "0" ? 15 : 11)
    end
  end

  def get_size
    unless operator?
      index = 6

      loop do
        prefix = bin[index]
        index += 5
        break if prefix == "0"
      end

      index
    else
      header_size + sub_packets.map(&:size).sum
    end
  end

  def size
    @size ||= get_size
  end

  def version_numbers_sum
    version + sub_packets.map(&:version_numbers_sum).sum
  end

  def value
    return sub_packets.first.value if sub_packets.one?

    case type_id
    when 0 # sum
      sub_packets.map(&:value).sum
    when 1 # product
      sub_packets.reduce(1) { |acc, packet| acc * packet.value }
    when 2 # min
      sub_packets.min_by { |packet| packet.value }.value
    when 3 # max
      sub_packets.max_by { |packet| packet.value }.value
    when 4 # literal value
      index = 6
      value_string = ""

      loop do
        prefix, *group = bin[index,5].chars
        value_string << group.join
        index += 5

        break if prefix == "0"
      end

      value_string.to_i(2)
    when 5 # greater than
      sub_packets.first.value > sub_packets.last.value ? 1 : 0
    when 6 # less than
      sub_packets.first.value < sub_packets.last.value ? 1 : 0
    when 7 # equal
      sub_packets.first.value == sub_packets.last.value ? 1 : 0
    end
  end
end
