[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.png"/>
</div>

## LibDriver LM75B

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/lm75b/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

LM75Bは、オンチップバンドギャップ温度センサーと過熱検出出力を備えたシグマデルタA/D変換技術を使用した温度-デジタルコンバーターです。 LM75Bには、いくつかのデータレジスタが含まれています：データシートに記載されているように、デバイス動作モード、OS動作モード、OS極性、OS障害キューなどのデバイス設定を格納する構成レジスタ（Conf）デジタルを格納する温度レジスタ（Temp）温度読み取り、およびプログラム可能な過熱シャットダウンとヒステリシス制限を格納するためのセットポイントレジスタ（TosおよびThyst）。これは、2線式シリアルI2Cバスインターフェイスを介してコントローラから通信できます。このデバイスには、温度がプログラムされた制限を超えるとアクティブになるオープンドレイン出力（OS）も含まれています。 3つの選択可能なロジックアドレスピンがあるため、アドレスの競合なしに8つのデバイスを同じバスに接続できます。LM75Bは、さまざまな動作条件に合わせて構成できます。周囲温度を定期的に監視するために通常モードに設定することも、消費電力を最小限に抑えるためにシャットダウンモードに設定することもできます。 OS出力は、OSコンパレータモードまたはOS割り込みモードの2つの選択可能なモードのいずれかで動作します。そのアクティブ状態は、HIGHまたはLOWのいずれかとして選択できます。 OS出力をアクティブにするために連続する障害の数を定義する障害キューは、設定値の制限と同様にプログラム可能です。温度レジスタは常に11ビットの2の補数データを格納し、0.125 Cの温度分解能を提供します。この高温分解能は、熱ドリフトまたは暴走を正確に測定するアプリケーションで特に役立ちます。 LM75Bにアクセスしても、処理中の変換は中断されず（つまり、I2Cバスセクションはシグマデルタコンバータセクションから完全に独立しています）、通信間の変換時間を少なくとも1回待たずに、LM75Bに継続的にアクセスしても、デバイスは、新しい変換結果で一時レジスタを更新しません。新しい変換結果は、Tempレジスタが更新された直後に利用可能になります。 LM75Bは、OSがコンパレータモード、温度しきい値が80 C、ヒステリシスが75 Cの通常動作モードで起動するため、事前定義された温度設定値でスタンドアロンのサーモスタットとして使用できます。LM75Bはシステムの熱管理、パーソナルコンピュータ、電子機器、産業用コントローラで使用されます。

LibDriver LM75Bは、LibDriverによって起動されたLM75Bの全機能ドライバーであり、温度読み取りや割り込み検出などの機能を提供します。 LibDriverはMISRAに準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example interrupt](#example-interrupt)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver LM75Bのソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver LM75B用のプラットフォームに依存しないIICバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver LM75Bドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver LM75Bプログラミング例が含まれています。

/ docディレクトリには、LibDriver LM75Bオフラインドキュメントが含まれています。

/ datasheetディレクトリには、LM75Bデータシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないIICバステンプレートを参照して、指定したプラットフォームのIICバスドライバを完成させます。

/ srcディレクトリ、/ interfaceディレクトリ、および/exampleディレクトリをプロジェクトに追加します。

### 使用

#### example basic

```C
uint8_t res;
uint8_t i;
float t;

res = lm75b_basic_init(LM75B_ADDRESS_A000);
if (res != 0)
{
    return 1;
}

...

for (i = 0; i < 3; i++)
{
    lm75b_interface_delay_ms(1000);
    res = lm75b_basic_read((float *)&t);
    if (res != 0)
    {
        (void)lm75b_basic_deinit();

        return 1;
    }
    lm75b_interface_debug_print("lm75b: temperature is %0.3fC.\n", t);

    ...
    
}

...

(void)lm75b_basic_deinit();

return 0;
```

#### example interrupt

```c
uint8_t res;
uint8_t i;
float t;
uint8_t g_flag;

res = gpio_interrupt_init();
if (res != 0)
{
    return 1;
}
res = lm75b_interrupt_init(LM75B_ADDRESS_A000, LM75B_OS_OPERATION_INTERRUPT, 22.5, 32.1);
if (res != 0)
{
    (void)gpio_interrupt_deinit();

    return 1;
}

...
    
for (i = 0; i < 3; i++)
{
    lm75b_interface_delay_ms(1000);
    res = lm75b_interrupt_read((float *)&t);
    if (res != 0)
    {
        (void)gpio_interrupt_deinit();
        (void)lm75b_interrupt_deinit();

        return 1;
    }
    lm75b_interface_debug_print("lm75b: read is %0.3fC.\n", t);
    
    ...
    
    if (g_flag != 0)
    {
        lm75b_interface_debug_print("lm75b: find interrupt.\n");

        break;
    }
    
    ...
    
}

...

(void)gpio_interrupt_deinit();
(void)lm75b_interrupt_deinit();

return 0;
```

### ドキュメント

オンラインドキュメント: https://www.libdriver.com/docs/lm75b/index.html

オフラインドキュメント: /doc/html/index.html

### 貢献

お問い合わせくださいlishifenging@outlook.com

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com