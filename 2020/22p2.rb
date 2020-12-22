top, bottom = STDIN.read.split("\n\n")

DEBUG = false

def dputs(*args)
  puts *args if DEBUG
end

p1_cards = top.split("\n")[1..-1].map(&:to_i)
p2_cards = bottom.split("\n")[1..-1].map(&:to_i)

ggame = 0

igp_rule = lambda do |hand_history|
  not hand_history.detect do |round|
    hand_history.count(round) > 1
  end.nil?
end

calc_score = lambda do |hand|
  score = 0
  hand.each_with_index do |card,i|
    score += card * (hand.length - i)
  end
  score
end

@memo = Hash.new { |h,k| h[k] = Hash.new }

play = lambda do |p1c, p2c|
  memo = @memo[p1c][p2c] || @memo[p2c][p1c]
  return memo unless memo.nil?

  round = 1
  ggame += 1
  game = ggame
  hand_history = []

  dputs "\n=== Game #{game} ===\n\n"
  dputs "Player 1's deck: #{p1c.inspect}"
  dputs "Player 2's deck: #{p2c.inspect}"

  until p1c.empty? || p2c.empty?
    dputs "\n-- Round #{round} (Game #{game}) --"

    if igp_rule.call(hand_history)
      dputs "Player 1 wins!"
      @memo[p1c][p2c] = :p1
      @memo[p2c][p1c] = :p1
      return :p1
    end

    hand_history.push [p1c.clone, p2c.clone]

    dputs "Player 1's deck: #{p1c.inspect}"
    dputs "Player 2's deck: #{p2c.inspect}"

    p1_pick = p1c.shift
    p2_pick = p2c.shift

    dputs "Player 1 plays: #{p1_pick}"
    dputs "Player 2 plays: #{p2_pick}"

    if p1c.count >= p1_pick && p2c.count >= p2_pick
      dputs "Playing a sub-game to determine the winner..."

      p1cc = p1c[0, p1_pick]
      p2cc = p2c[0, p2_pick]

      if play.call(p1cc, p2cc) == :p1
        @memo[p1cc][p2cc] = :p1
        @memo[p2cc][p1cc] = :p1
        dputs "Player 1 wins round #{round} of game #{game}!"
        p1c.push p1_pick
        p1c.push p2_pick
      else
        @memo[p1cc][p2cc] = :p2
        @memo[p2cc][p1cc] = :p2
        dputs "Player 2 wins round #{round} of game #{game}!"
        p2c.push p2_pick
        p2c.push p1_pick
      end
    else
      if p1_pick > p2_pick
        @memo[p1c][p2c] = :p1
        @memo[p2c][p1c] = :p1
        dputs "Player 1 wins round #{round} of game #{game}!"
        p1c.push p1_pick
        p1c.push p2_pick
      else
        @memo[p1c][p2c] = :p2
        @memo[p2c][p1c] = :p2
        dputs "Player 2 wins round #{round} of game #{game}!"
        p2c.push p2_pick
        p2c.push p1_pick
      end
    end

    round += 1
  end

  if p1c.empty?
    dputs "The winner of game #{game} is player 2!"
    puts "hand: #{p2c.inspect}\nscore: #{calc_score.call(p2c)}, hhsize: #{hand_history.size}, memosize: #{@memo.size}"
    :p2
  else
    dputs "The winner of game #{game} is player 1!"
    puts "hand: #{p1c.inspect}\nscore: #{calc_score.call(p1c)}, hhsize: #{hand_history.size}, memosize: #{@memo.size}"
    :p1
  end
end

p play.call(p1_cards, p2_cards)
