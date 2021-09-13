class Rational
  def *(rhs)
    if rhs.is_a? Rational
      Rational(numerator.to_f * rhs.numerator, denominator.to_f * rhs.denominator)
    elsif rhs.is_a?(Integer) || rhs.is_a?(Float)
      Rational(numerator.to_f * rhs, denominator.to_f)
    elsif rhs.is_a? Numeric
      numerator * rhs / denominator.to_f
    end
  end

  def +(rhs)
    if rhs.is_a? Rational
      Rational(numerator.to_f * rhs.denominator + rhs.numerator.to_f * denominator, denominator.to_f * rhs.denominator)
    elsif rhs.is_a?(Integer) || rhs.is_a?(Float)
      Rational(numerator.to_f + rhs * denominator.to_f, denominator.to_f)
    elsif rhs.is_a? Numeric
      (numerator + rhs * denominator) / denominator
    end
  end

  def -(rhs)
    if rhs.is_a? Rational
      Rational(numerator.to_f * rhs.denominator - rhs.numerator.to_f * denominator, denominator.to_f * rhs.denominator)
    elsif rhs.is_a?(Integer) || rhs.is_a?(Float)
      Rational(numerator.to_f - rhs.to_f * denominator, denominator.to_f)
    elsif rhs.is_a? Numeric
      (numerator - rhs * denominator) / denominator
    end
  end

  def /(rhs)
    if rhs.is_a? Rational
      Rational(numerator.to_f * rhs.denominator, denominator.to_f * rhs.numerator)
    elsif rhs.is_a?(Integer) || rhs.is_a?(Float)
      Rational(numerator.to_f, denominator.to_f * rhs)
    elsif rhs.is_a? Numeric
      numerator / rhs / denominator
    end
  end
end
