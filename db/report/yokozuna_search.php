<HTML>
<HEAD>
  <TITLE>横綱の検索結果</TITLE>
  <META http-equiv="Content-Type" content="text/html; charset=UTF-8">
</HEAD>
<BODY>

<CENTER>

検索結果を表示します。<BR><BR>

<!-- ここからPHPのスクリプト始まり -->
<?php

// 検索フォームから渡された引数を取得
$room_no = (string)$_GET[ room_no ];

// データベースに接続
// ※ your_db_name のところは自分のデータベース名に書き換える
$conn = pg_connect( "dbname=agdo2465" );

// 接続が成功したかどうか確認
if ( $conn == null )
{
	print( "データベース接続処理でエラーが発生しました。<BR>" );
	exit;
}

// SQLを作成（検索フォームで全ての部門が指定された場合は全部門の従業員を検索し、それ以外の場合は、指定された部門の従業員を検索）
if ( $room_no == "ALL" )
	$sql ="select id, yokozuna.name, fro, promo_year, room.name from yokozuna,room where yokozuna.room_no = room.room_no order by id ASC"; // ※ 全部屋の横綱を検索
else
	$sql ="select id, yokozuna.name, fro, promo_year, room.name from yokozuna,room where yokozuna.room_no = room.room_no and room.room_no = '$room_no' order by id ASC"; // ※ 指定された部門番号（$room_no）の従業員を検索

// Queryを実行して検索結果をresultに格納
$result = pg_query( $conn, $sql );
if ( $result == null )
{
	print( "クエリー実行処理でエラーが発生しました。<BR>" );
	print( "クエリー「" . $sql  . "」を実行。<BR>" );
	exit;
}

// 検索結果の行数・列数を取得
$rows = pg_num_rows( $result );
$cols = pg_num_fields( $result );


// 検索結果をテーブルとして表示
print( "<TABLE BORDER=1>\n" );

// 各列の名前を表示
print( "<TR>" );
print( "<TH>横綱番号</TH>" );
print( "<TH>部屋</TH>" );
print( "<TH>四股名</TH>" );
print( "<TH>出身</TH>" );
print( "<TH>横綱出身年/TH>" );
print( "</TR>\n" );

// 各行のデータを表示
for ( $j=0; $j<$rows; $j++ )
{
	print( "<TR>" );
	for ( $i=0; $i<$cols; $i++ )
	{
		// j行i列のデータを取得
		$data = pg_fetch_result( $result, $j, $i );
		
		// セルに列の名前を表示
		print( "<TD> $data </TD>" );
	}
	print( "</TR>\n" );
}

// ここまででテーブル終了
print( "</TABLE>" );
print( "<BR>\n" );


// 検索件数を表示
print( "以上、$rows 件のデータを表示しました。<BR>\n" );


// 検索結果の開放
pg_free_result( $result );

// データベースへの接続を解除
pg_close( $conn );

?>
<!-- ここまででPHPのスクリプト終わり -->

<BR>
<A HREF="menu.html">操作メニューに戻る</A>

</CENTER>

</BODY>
</HTML>

