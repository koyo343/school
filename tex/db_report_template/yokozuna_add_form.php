<HTML>
<HEAD>
  <TITLE>横綱データ追加フォーム（動的生成版）</TITLE>
  <META http-equiv="Content-Type" content="text/html; charset=UTF-8">
</HEAD>
<BODY>

横綱データ 追加フォーム<BR><BR>

<FORM ACTION="yokozuna_add.php" METHOD="GET">

<!-- ここからPHPのスクリプト始まり -->
<?php

// データベースに接続
// ※ your_db_name のところは自分のデータベース名に書き換える
$conn = pg_connect( "dbname=agdo2465" );

// 接続が成功したかどうか確認
if ( $conn == null )
{
	print( "データベース接続処理でエラーが発生しました。<BR>" );
	exit;
}


// 最も大きな従業員番号を取り出すSQLの作成
$sql = "select max(id) from yokozuna";

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
print( "横綱代数：\n" );
printf( "<INPUT TYPE=text SIZE=2 NAME=id VALUE=%02s>", $max_id ); // 必ず2桁で出力、空白があれば0で埋める
print( "<BR>\n" );

// 検索結果の開放
pg_free_result( $result );


// 部屋一覧を取得するSQLの作成
$sql = "select room_no, name from room";

// Queryを実行して検索結果をresultに格納
$result = pg_query( $conn, $sql );
if ( $result == null )
{
	print( "クエリー実行処理でエラーが発生しました。<BR>" );
	exit;
}

// 検索結果の行数を取得
$rows = pg_num_rows( $result );

// 部屋の数だけ選択肢を出力
print( "部屋：\n" );
for ( $i=0; $i<$rows; $i++ )
{
	$room_no = pg_fetch_result( $result, $i, 0 );
	$room_name = pg_fetch_result( $result, $i, 1 );
	printf( "<INPUT TYPE=\"radio\" NAME=\"room_no\" VALUE=\"%s\"> %s </INPUT>\n", $room_no, $room_name );
}

// 検索結果の開放
pg_free_result( $result );

// データベースへの接続を解除
pg_close( $conn );

?>
<!-- ここまででPHPのスクリプト終わり -->

<BR>

四股名：
<INPUT TYPE="text" SIZE="7" NAME="name">

横綱昇進年：
<INPUT TYPE="text" SIZE="4" NAME="promo_year">

出身：
<INPUT TYPE="text" SIZE="4" NAME="fro">

<BR><BR>
<INPUT TYPE="submit" VALUE="送信"><BR>

</FORM>

</BODY>
</HTML>
