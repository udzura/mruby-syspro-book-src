class CalcPI
  def initialize(precision: 100)
    @precision = precision
  end
  attr_reader :precision

  def leibniz
    pion4 = 0r
    (0..precision).each do |n|
      delta = Rational((-1) ** n) / (2 * n + 1)
      pion4 = pion4 + delta
    end
    return (pion4 * 4).to_f
  end

  def gauss_l(iteration: 6)
    a = 1r
    b = 1r / babylonian_sqrt(2)
    t = 0.25r
    p_ = 1r

    (1..iteration).each do
      an = (a + b) / 2
      b = babylonian_sqrt(a * b)
      t -= p_ * (an - a) * (an - a)
      p_ *= 2
      a = an
    end

    ((a + b) * (a + b) / (4 * t)).to_f
  end

  def babylonian_sqrt(num, as_f: false)
    num = Rational(num) unless num.is_a? Rational
    ret = Rational(precision, 2)
    (1..precision).each do |i|
      ret = (ret + num / ret) / 2
    end
    as_f ? ret.to_f : ret
  end
end
