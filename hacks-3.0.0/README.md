# mruby 3.0.0 の対応について

* まず、本書の第1版はmruby 2.1.2 にのみ対応します。
* 3.0.0 での動作検証を本ディレクトリ配下で徐々に進めていますが、あくまで筆者によるボランティアで、NO WARANTYです。
* このREADMEでは、対応内容の詳細をなるべく解説します。

## CHAPTER 03 mgemを作ってみよう

* p.62 掲載のライプニッツの公式の実装は、そのままでは3.0.0で動作しません。
* 同様に p.64 のバビロニアの平方根のアルゴリズムも動作しません。

```console
trace (most recent call last):
        [2] rat.rb:43
        [1] rat.rb:9:in leibniz
rat.rb:11:in leibniz: integer overflow (RangeError)
```

```console
trace (most recent call last):
        [3] rat.rb:43
        [2] rat.rb:18:in gauss_l
        [1] rat.rb:36:in babylonian_sqrt
rat.rb:37:in babylonian_sqrt: integer overflow (RangeError)
```

* 原因としては、
  * mruby 3.0.0より、mruby-rational のインスタンス生成時に、 numerator 、 denominator の両方についてintの範囲を超えたら例外にするようになった。 [commit](https://github.com/mruby/mruby/commit/cc59860e4077aa5f3dbd398639c84b9214ec5d7d)
  * mruby 2.1.2 までは、 `DROP_PRECISION()` と言うマクロがあろ、rationalのnumerator 、 denominator がオーバーフローしそうな際にintの範囲に納めていた。

ということで、p.62以降の内容は、実際には精度を落としながら計算を続けていたことになります。本内容はあくまでmgemの実装のサンプルで、正確な数値計算を目的とはしていないという点を留意して学習にお使いください。

また、mruby 3.0においては本ディレクトリ配下の `chapter02/00_rational_hack.rb` というファイルを生成されたmgemの `mrblib` に含めることで開発を続けることができます。 `DROP_PRECISION()` の挙動の再現にはCレベルの変更が必要なため、2.1系と同じ挙動にはなっていません。ご注意ください。本章の意図には影響ないと判断し公開します。

