assert("CalcPI#leipniz") do
  res = CalcPI.new.leibniz.to_s
  assert_equal("3.1", res[0, 3])
end

assert("CalcPI#leipniz 3rd decimal") do
  res = CalcPI.new(precision: 3000).leibniz.to_s
  assert_equal("3.141", res[0, 5])
end

assert("CalcPI#babylonian_sqrt as Rational") do
  res = CalcPI.new.babylonian_sqrt(2)
  assert_equal(
    Rational(6632452706042512, 4689852284341727),
    res)
end

assert("CalcPI#babylonian_sqrt as Float") do
  res = CalcPI.new.babylonian_sqrt(2, as_f: true).to_s
  assert_equal("1.414213562373095", res[0, 17])
end

assert("CalcPI#gauss_l") do
  res = CalcPI.new.gauss_l.to_s
  assert_equal("3.14159265358979", res[0, 16])
end

assert("CalcPI#gauss_l 15th decimal") do
  res = CalcPI.new.gauss_l(iteration: 10).to_s
  assert_equal("3.141592653589793", res[0, 17])
end
