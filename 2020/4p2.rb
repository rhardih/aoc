require "set"

input = STDIN.read.split("\n\n")

required_fields = ["byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"].to_set
valid_passports = 0

input.each do |line|
  fields = line.tr("\n", " ").split(" ").map { |f| f.split(":") }.to_h

  has_required_fields = fields.keys.to_set & required_fields == required_fields

  next unless has_required_fields

  byr_valid = fields["byr"].to_i.then { |year| 1920 <= year && year <= 2002 }
  iyr_valid = fields["iyr"].to_i.then { |year| 2010 <= year && year <= 2020 }
  eyr_valid = fields["eyr"].to_i.then { |year| 2020 <= year && year <= 2030 }
  hgt_valid = fields["hgt"].then do |height|
    case height
    when /^(\d+)cm$/
      150 <= $1.to_i && $1.to_i <= 193
    when /^(\d+)in$/
      59 <= $1.to_i && $1.to_i <= 76
    end
  end
  hcl_valid = fields["hcl"].then do |hair_color|
    (/^#[0-9a-f]{6}$/ =~ hair_color) != nil
  end
  ecl_valid = fields["ecl"].then do |eye_color|
    %w{amb blu brn gry grn hzl oth}.include?(eye_color)
  end
  pid_valid = fields["pid"].then do |passport_id|
    (/^\d{9}$/ =~ passport_id) != nil
  end

  if byr_valid &&
      iyr_valid &&
      eyr_valid &&
      hgt_valid &&
      hcl_valid &&
      ecl_valid &&
      pid_valid

    valid_passports += 1
  end
end

puts "Valid passports: #{valid_passports}"
