<HTML>
<HEAD>
  <TITLE>横綱データ更新フォーム</TITLE>
  <META http-equiv="Content-Type" content="text/html; charset=UTF-8">
</HEAD>
<BODY>

横綱データ 更新フォーム<BR><BR>

<FORM ACTION="yokozuna_update.php" METHOD="GET">

<!-- ここからPHPのスクリプト始まり -->
<?php

// 引数の横綱代数を取得
$id = (string) $_GET[ id ];

// データベースに接続
// ※ your_db_name のところは自分のデータベース名に書き換える
$conn = pg_connect( "dbname=agdo2465" );

// 接続が成功したかどうか確認
if ( $conn == null )
{
    print( "データベース接続処理でエラーが発生しました。<BR>" );
    exit;
}

// 指定された横綱番号のエージェント情報を取得するSQLを作成
$sql = sprintf( "select id, name, fro, promo_year from yokozuna where id='%s'", $id );

// Queryを実行して検索結果をresultに記録
$result = pg_query( $conn, $sql );
if ( $result == null )
{
    print( "クエリー実行処理でエラーが発生しました。<BR>" );
    exit;
}

//横綱が見つからなければエラーメッセージを表示
if ( pg_num_rows( $result ) == 0 )
{
    print( "指定された横綱代数のデータが見つかりません。<BR>\n" );
    exit;
}

// 検索結果のエージェントの情報を変数に記録
$curr_id = pg_fetch_result( $result, 0, 0 );
$curr_name = pg_fetch_result( $result, 0, 1 );
$curr_fro = pg_fetch_result( $result, 0, 2 );
$curr_promo_year  = pg_fetch_result( $result, 0, 3 );


// 検索結果の開放
pg_free_result( $result );

// 横綱代数を更新スクリプトに渡す
printf( "<INPUT TYPE=hidden NAME=id VALUE=%s>\n", $id);


// 部屋一覧を取得するSQLの作成
$sql = "select room_no, name fro room";

// Queryを実行して検索結果をresultに記録
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
    $id = pg_fetch_result( $result, $i, 0 );
    $room = pg_fetch_result( $result, $i, 1 );
    
    if ( $id == $curr_id )
        $checked = "CHECKED";
    else
        $checked = "";
    
    printf( "<INPUT TYPE=radio NAME=id VALUE=%s %s> %s </INPUT>\n", $id, $checked, $room );
}

// 検索結果の開放
pg_free_result( $result );
// データベースへの接続を解除
pg_close( $conn );

// 氏名の入力フィールドを出力
print( "<BR>\n" );
print( "四股名：\n" );
printf( "<INPUT TYPE=text SIZE=7 NAME=name VALUE=\"%s\">\n", $curr_name );
print( "\n" );

// 出身の入力フィールドを出力
print( "出身：\n" );
printf( "<INPUT TYPE=text SIZE=4 NAME=fro VALUE=%s>\n", $curr_fro );

// 横綱昇進年の入力フィールドを出力
print( "横綱昇進年：\n" );
printf( "<INPUT TYPE=text SIZE=4 NAME=promo_year   VALUE=%s>\n", $curr_promo_year   )

?>
<!-- ここまででPHPのスクリプト終わり -->

<BR>



<BR><BR>
<INPUT TYPE="submit" VALUE="送信"><BR>

</FORM>

</BODY>
</HTML>