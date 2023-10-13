# minishell
This is work space of "minishll" (one of 42cursus project).

# to think.
・ check all function's document.  
・ read minishell repo.  
・ understand about "lexer" & "parser".  

# to do
・ 閉じられていない引用符や、指定されていない特殊文字（\ や ;）を解釈する必要はない  
・ 1つ以上のグローバル変数を使用してはいけません。また、そうする理由を考えて、説明する準備をしてください  
・ コマンドの入力を待機する際、プロンプト(訳者註: 入力開始位置を示す文字)を表示してください  
・ working histroy(訳者註: 実行したコマンドの履歴)を保持してください  
・ PATH変数および相対パス/絶対パスを用いて入力されたコマンドの正しい実行ファイルを探し出し、起動してください  
・ 以下のビルトインコマンドを実装してください  
	*echo （-n オプションの挙動を含む）  
 	*cd　（相対パス、または絶対パスのみで動作する）  
 	*pwd　（オプションの処理を含まない）  
   	*export　（オプションの処理を含まない）  
   	*unset　（オプションの処理を含まない）  
   	*env　（オプションと引数の処理を含まない）  
   	*exit　（オプションの処理を含まない）  
・ 「'」は、すべてのシーケンス文字の解釈を抑制します  
・ 「"」 は、「$」をのぞくすべてのシーケンス文字の解釈を抑制します  
・ リダイレクト  
	*「<」で、入力のリダイレクトを行ってください  
 	*「>」で、出力のリダイレクトを行ってください  
 	*「<<」では、現在の入力元から区切り文字列だけを含む行が現れるまで読み込みます。履歴の更新は必要ありません！  
	*「>>」は、出力のリダイレクトを追記モードで行ってください  
・ パイプ「|」は、パイプラインの各コマンドの出力結果を、パイプを通して次のコマンドの入力につなげます  
・ 環境変数（「$」に続く文字列）は、その値に展開してください  
・ 「$?」は、直近にフォアグラウンドで実行されたパイプラインのコマンドの終了ステータスを展開してください  
・ 「ctrl-C」、「ctrl-D」、そして「ctrl-\」は、bashの場合と同じ結果となるようにしてください  
・ インタラクティブのとき（訳者註: コマンド入力待ちの状態で）：  
	*Ctrl - C : 次の行に、プロンプトを表示してください  
	*Ctrl - D : シェルを終了してください✅  
	*Ctrl - \ : 何も行わないでください  

# function memo
 readline  `char *readline (char *prompt);` `prompt`で指定された文字を行頭に表示しつつ、返り値に読み取った行を返す。返り値に'\n'は含まれない。　空白行は空白の文字列を返す。行の読み取り中にEOFが検出され、その行が空の時、NULLを返す。EOFが検出されたが、その行が空でない場合、EOFは改行として扱われる。  
 rl_clear_history  `int	rl_on_new_line(void);`   
 rl_on_new_line  
 rl_replace_line  
 rl_redisplay  
 add_history  
 printf  
 malloc  
 free  
 write  
 access  
 open  
 read  
 close  
 fork  
 wait  
 waitpid  
 wait3  
 wait4  
 signal  
 sigaction  
 sigemptyset  
 sigaddset  
 kill  
 exit  
 getcwd  
 chdir  
 stat  
 lstat  
 fstat  
 unlink  
 execve  
 dup  
 dup2  
 pipe  
 opendir  
 readdir  
 closedir  
 strerror  
 perror  
 isatty  
 ttyname  
 ttyslot  
 ioctl  
 getenv  
 tcsetattr  
 tcgetattr  
 tgetent  
 tgetflag  
 tgetnum  
 tgetstr  
 tgoto  
 tputs  
