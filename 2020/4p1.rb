require "set"

input = STDIN.read.split("\n\n")

required_fields = ["byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"].to_set
valid_passports = 0

input.each do |line|
  fields = line.tr("\n", " ").split(" ").map { |f| f[0..2] }.to_set
  valid_passports += 1 if required_fields <= fields
end

puts "Valid passports: #{valid_passports}"
