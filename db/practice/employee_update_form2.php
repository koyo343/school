<HTML>
<HEAD>
  <TITLE>従業員データ更新フォーム</TITLE>
  <META http-equiv="Content-Type" content="text/html; charset=UTF-8">
</HEAD>
<BODY>

従業員データ 更新フォーム<BR><BR>

<FORM ACTION="employee_update.php" METHOD="GET">

<!-- ここからPHPのスクリプト始まり -->
<?php

// 引数の従業員番号を取得
$id = (string) $_GET[ id ];

// データベースに接続
// ※ your_db_name のところは自分のデータベース名に書き換える
$conn = pg_connect( "dbname=your_db_name" );

// 接続が成功したかどうか確認
if ( $conn == null )
{
	print( "データベース接続処理でエラーが発生しました。<BR>" );
	exit;
}

// 指定された従業員番号の従業員情報を取得するSQLを作成
$sql = sprintf( "select dept_no, name, age from employee where id='%s'", $id );

// Queryを実行して検索結果をresultに記録
$result = pg_query( $conn, $sql );
if ( $result == null )
{
	print( "クエリー実行処理でエラーが発生しました。<BR>" );
	exit;
}

// 従業員が見つからなければエラーメッセージを表示
if ( pg_num_rows( $result ) == 0 )
{
	print( "指定された従業員番号のデータが見つかりません。<BR>\n" );
	exit;
}

// 検索結果の従業員の情報を変数に記録
$curr_dept_no = pg_fetch_result( $result, 0, 0 );
$curr_name = pg_fetch_result( $result, 0, 1 );
$curr_age = pg_fetch_result( $result, 0, 2 );

// 検索結果の開放
pg_free_result( $result );

// 従業員番号を更新スクリプトに渡す
printf( "<INPUT TYPE=hidden NAME=id VALUE=%s>\n", $id );


// 部門一覧を取得するSQLの作成
$sql = "select dept_no, name from department";

// Queryを実行して検索結果をresultに記録
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
	
	if ( $dept_no == $curr_dept_no )
		$checked = "CHECKED";
	else
		$checked = "";
	
	printf( "<INPUT TYPE=radio NAME=dept_no VALUE=%s %s> %s </INPUT>\n", $dept_no, $checked, $dept_name );
}

// 検索結果の開放
pg_free_result( $result );

// データベースへの接続を解除
pg_close( $conn );

// 氏名の入力フィールドを出力
print( "<BR>\n" );
print( "氏名：\n" );
printf( "<INPUT TYPE=text SIZE=24 NAME=name VALUE=\"%s\">\n", $curr_name );
print( "　\n" );

// 年齢の入力フィールドを出力
print( "年齢：\n" );
printf( "<INPUT TYPE=text SIZE=4 NAME=age VALUE=%s>\n", $curr_age );

?>
<!-- ここまででPHPのスクリプト終わり -->

<BR>

性別：
<INPUT TYPE="radio" NAME="sex" VALUE="MALE" CHECKED>男</INPUT>
<INPUT TYPE="radio" NAME="sex" VALUE="FIMALE">女</INPUT>

<BR><BR>
<INPUT TYPE="submit" VALUE="送信"><BR>

</FORM>

</BODY>
</HTML>
