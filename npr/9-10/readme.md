# fact.cgi Execution Guide (fact.cgi 実行ガイド)

## Problem (問題)
When accessing `fact.html` and submitting the form, an "Internal Server Error" occurs. 
This happens because the web server (Apache) is configured to execute CGI scripts from the `/usr/lib/cgi-bin/` directory, but the compiled `fact.cgi` file is located in the local project directory.

`'fact.html'にアクセスしてフォームを送信すると "Internal Server Error" が発生します。
これは、Webサーバー（Apache）がCGIスクリプトを/usr/lib/cgi-bin/ディレクトリから実行するように設定されているにもかかわらず、コンパイルされた'fact.cgi'ファイルがローカルのプロジェクトディレクトリに配置されているために起こります。`

## Solution (解決策)
Follow these steps in the terminal to resolve the issue.

`この問題を解決するには、ターミナルで以下の手順に従ってください。`

### 1. Compile the C Source Code (Cソースコードをコンパイルする)
First, compile `fact.c` to create the executable `fact.cgi`.

`まず、'fact.c'をコンパイルして実行ファイル'fact.cgi'を作成します。`

```bash
gcc fact.c -o fact.cgi
```

### 2. Copy the Executable to the cgi-bin Directory (実行ファイルをcgi-binディレクトリにコピーする)
Next, copy the compiled `fact.cgi` to the directory where Apache expects CGI scripts. You will need `sudo` privileges for this.

`次に、コンパイルされた'fact.cgi'をApacheがCGIスクリプトを配置する想定のディレクトリにコピーします。これには'sudo'権限が必要です。`

```bash
sudo cp fact.cgi /usr/lib/cgi-bin/
```

### 3. Ensure Execute Permissions (実行権限を付与する)
Finally, ensure the copied file has the correct execute permissions. While `cp` often preserves permissions, it's good practice to verify.

`最後に、コピーしたファイルに正しい実行権限が付与されていることを確認します。'cp'コマンドは権限を保持することが多いですが、念のため確認するのが良い習慣です。`

```bash
sudo chmod 755 /usr/lib/cgi-bin/fact.cgi
```

After completing these steps, the form in `fact.html` should correctly execute the `fact.cgi` script and display the expected output.

`これらの手順を完了すると、'fact.html'のフォームが'fact.cgi'スクリプトを正しく実行し、期待される出力が表示されるはずです。`

## extract.c Local Testing Guide (extract.c ローカルテストガイド)

`extract.c` はCGIスクリプトとして設計されており、Webサーバー環境なしでコマンドラインからその動作をシミュレートして確認できます。

### 1. Compile the C Source Code (Cソースコードをコンパイルする)

まず、`extract.c` をコンパイルして実行ファイルを作成します。

```bash
gcc -o extract.cgi extract.c
```

### 2. Simulate GET Request (GETリクエストのシミュレーション)

GETリクエストは、`QUERY_STRING` 環境変数にデータを設定することでシミュレートできます。(絶対パスで指定)

```bash
QUERY_STRING="name=John+Doe&age=30" /~/extract.cgi
```

### 3. Simulate POST Request (POSTリクエストのシミュレーション)

POSTリクエストは、`REQUEST_METHOD` 環境変数を `POST` に設定し、標準入力にデータを渡すことでシミュレートできます。(絶対パス)

```bash
echo "data=Hello+World&id=123" | REQUEST_METHOD="POST" /~/extract.cgi
```