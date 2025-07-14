<HTML>
<HEAD>
  <TITLE>従業員データ追加フォーム（動的生成版）</TITLE>
  <META http-equiv="Content-Type" content="text/html; charset=UTF-8">
</HEAD>
<BODY>

従業員データ 追加フォーム<BR><BR>

<FORM ACTION="employee_add.php" METHOD="GET">

<!-- ここからPHPのスクリプト始まり -->
<?php

// データベースに接続
// ※ your_db_name のところは自分のデータベース名に書き換える
$conn = pg_connect( "dbname=your_db_name" );

// 接続が成功したかどうか確認
if ( $conn == null )
{
	print( "データベース接続処理でエラーが発生しました。<BR>" );
	exit;
}


// 最も大きな従業員番号を取り出すSQLの作成
$sql = "select max(id) from employee";

// Queryを実行して検索結果をresultに格納
$result = pg_query( $conn, $sql );
if ( $result == null )
{
	print( "クエリー実行処理でエラーが発生しました。<BR>" );
	exit;
}

// 最大の従業員番号を取得
if ( pg_num_rows( $result ) > 0 )
	$max_id = pg_fetch_result( $result, 0, 0 );
$max_id ++;

// 従業員番号の初期値を指定して入力エリアを作成
print( "従業員番号：\n" );
printf( "<INPUT TYPE=text SIZE=4 NAME=id VALUE=%04s>", $max_id ); // 必ず４桁で出力、空白があれば0で埋める
print( "<BR>\n" );

// 検索結果の開放
pg_free_result( $result );


// 部門一覧を取得するSQLの作成
$sql = "select dept_no, name from department";

// Queryを実行して検索結果をresultに格納
$result = pg_query( $conn, $sql );
if ( $result == null )
{
	print( "クエリー実行処理でエラーが発生しました。<BR>" );
	exit;
}

// 検索結果の行数を取得
$rows = pg_num_rows( $result );

// 部門の数だけ選択肢を出力
print( "部門：\n" );
for ( $i=0; $i<$rows; $i++ )
{
	$dept_no = pg_fetch_result( $result, $i, 0 );
	$dept_name = pg_fetch_result( $result, $i, 1 );
	printf( "<INPUT TYPE=\"radio\" NAME=\"dept_no\" VALUE=\"%s\"> %s </INPUT>\n", $dept_no, $dept_name );
}

// 検索結果の開放
pg_free_result( $result );

// データベースへの接続を解除
pg_close( $conn );

?>
<!-- ここまででPHPのスクリプト終わり -->

<BR>

氏名：
<INPUT TYPE="text" SIZE="24" NAME="name">
　
年齢：
<INPUT TYPE="text" SIZE="4" NAME="age">

性別：
<INPUT TYPE="radio" NAME="sex" VALUE="MALE" CHECKED>男</INPUT>
<INPUT TYPE="radio" NAME="sex" VALUE="FIMALE">女</INPUT>

<BR><BR>
<INPUT TYPE="submit" VALUE="送信"><BR>

</FORM>

</BODY>
</HTML>
