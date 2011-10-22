package com.yingql.android.games.zhaocha.core;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.database.sqlite.SQLiteDatabase;

import com.wiyun.engine.nodes.CharMap;
import com.wiyun.engine.opengl.TextureManager;
import com.wiyun.engine.sound.AudioManager;
import com.wiyun.engine.types.WYRect;
import com.wiyun.engine.utils.ResolutionIndependent;
import com.yingql.android.games.zhaocha.MainActivity;
import com.yingql.android.games.zhaocha.R;
import com.yingql.android.games.zhaocha.entity.Archive;
import com.yingql.android.games.zhaocha.entity.GameInfo;
import com.yingql.android.games.zhaocha.entity.GameMode;
import com.yingql.android.games.zhaocha.entity.GameStates;
import com.yingql.android.games.zhaocha.entity.UserInfo;
import com.yingql.android.games.zhaocha.scene.GameScene;
import com.yingql.android.games.zhaocha.scene.StartScene;
import com.yingql.android.games.zhaocha.sprite.GameInfoBoard;
import com.yingql.android.games.zhaocha.util.ArchiveHelper;
import com.yingql.android.games.zhaocha.util.GameUtil;
import com.yingql.android.games.zhaocha.util.WiGameUtil;
import com.yingql.android.games.zhaocha.util.db.DataBaseMetaData;
import com.yingql.android.games.zhaocha.util.db.DatabaseHelper;
import com.yingql.android.games.zhaocha.util.db.DatabaseOperator;

/**
 * 游戏中的各种重要方法和核心参数
 * 
 * @author yingql
 * 
 */
public class GameSystem
{
	private static GameInfo gameInfo = new GameInfo();

	/**
	 * 屏幕宽度
	 */
	public static float Screen_Width = 0;

	/**
	 * 屏幕高度
	 */
	public static float Screen_Height = 0;

	/**
	 * 总共的图片数量
	 */
	public static final int IMAGE_COUNT = 50;

	public static GameStates GameState = GameStates.Ready;

	public static CharMap RedCharMap;
	public static CharMap BlackCharMap;
	public static CharMap WhiteCharMap;

	public static GameInfo getGameInfo()
	{
		return gameInfo;
	}

	public static void loadAllResource()
	{
		initDatabase();
		initCharMap();
		loadTexture();
		loadSound();
		loadScene();
	}

	private static void initDatabase()
	{
		DatabaseHelper helper = new DatabaseHelper(MainActivity.Instance, DataBaseMetaData.DATABASE_NAME);
		SQLiteDatabase db = helper.getWritableDatabase();
		if (db.isOpen())
			db.close();
	}

	private static void initCharMap()
	{
		WhiteCharMap = CharMap.make();
		WhiteCharMap.autoRelease();
		RedCharMap = CharMap.make();
		RedCharMap.autoRelease();
		BlackCharMap = CharMap.make();
		BlackCharMap.autoRelease();

		float offsetX = 0, offsetY = 0;
		float span10 = ResolutionIndependent.resolveDp(10);
		float span12 = ResolutionIndependent.resolveDp(12);
		float span18 = ResolutionIndependent.resolveDp(18);
		for (int i = 0; i < 10; i++)
		{
			BlackCharMap.mapChar(WYRect.make(offsetX, offsetY, span12, span18), '0' + i);
			offsetX += span12;
		}
		BlackCharMap.mapChar(WYRect.make(offsetX, offsetY, span18, span18), 'X');
		offsetX += span18;
		BlackCharMap.mapChar(WYRect.make(offsetX, offsetY, span18, span18), 'N');
		offsetX += span18;
		BlackCharMap.mapChar(WYRect.make(offsetX, offsetY, span18, span18), 'A');
		offsetX += span18;
		BlackCharMap.mapChar(WYRect.make(offsetX, offsetY, span18, span18), '/');
		offsetX += span18;
		BlackCharMap.mapChar(WYRect.make(offsetX, offsetY, span18, span18), ':');
		offsetY += span18;
		offsetX = 0;
		for (int i = 0; i < 10; i++)
		{
			RedCharMap.mapChar(WYRect.make(offsetX, offsetY, span12, span18), '0' + i);
			offsetX += span12;
		}
		RedCharMap.mapChar(WYRect.make(offsetX, offsetY, span18, span18), 'X');
		offsetX += span18;
		RedCharMap.mapChar(WYRect.make(offsetX, offsetY, span18, span18), 'N');
		offsetX += span18;
		RedCharMap.mapChar(WYRect.make(offsetX, offsetY, span18, span18), 'A');
		offsetX += span18;
		RedCharMap.mapChar(WYRect.make(offsetX, offsetY, span18, span18), '/');
		offsetX += span18;
		RedCharMap.mapChar(WYRect.make(offsetX, offsetY, 18, 18), ':');
		offsetY += span18;
		offsetX = 0;
		for (int i = 0; i < 10; i++)
		{
			WhiteCharMap.mapChar(WYRect.make(offsetX, offsetY, span12, span18), '0' + i);
			offsetX += span12;
		}
		WhiteCharMap.mapChar(WYRect.make(offsetX, offsetY, span18, span18), 'X');
		offsetX += span18;
		WhiteCharMap.mapChar(WYRect.make(offsetX, offsetY, span18, span18), 'N');
		offsetX += span18;
		WhiteCharMap.mapChar(WYRect.make(offsetX, offsetY, span18, span18), 'A');
		offsetX += span18;
		WhiteCharMap.mapChar(WYRect.make(offsetX, offsetY, span18, span18), '/');
		offsetX += span18;
		WhiteCharMap.mapChar(WYRect.make(offsetX, offsetY, span18, span18), ':');
		offsetX += span18;
		WhiteCharMap.mapChar(WYRect.make(offsetX, offsetY, span10, span18), '.');
	}

	private static void loadScene()
	{
		StartScene.make();
		GameScene.make();
	}

	private static void loadTexture()
	{
	}

	private static void loadSound()
	{
		AudioManager.preloadEffect(R.raw.alarm, AudioManager.FORMAT_OGG);
		AudioManager.preloadEffect(R.raw.clock, AudioManager.FORMAT_OGG);
		AudioManager.preloadEffect(R.raw.right, AudioManager.FORMAT_OGG);
		AudioManager.preloadEffect(R.raw.wrong, AudioManager.FORMAT_OGG);
	}

	public static void playEffect(int id)
	{
		if (DatabaseOperator.getUserInfo().isMusicOn())
		{
			AudioManager.playEffect(id);
		}
	}

	public static void playBGMusic()
	{
		if (DatabaseOperator.getUserInfo().isMusicOn() && !AudioManager.isBackgroundPlaying())
			AudioManager.playBackgroundMusic(R.raw.bg, AudioManager.FORMAT_OGG, -1);
	}

	public static void stopBGMusic()
	{
		if (AudioManager.isBackgroundPlaying())
			AudioManager.stopBackgroundMusic();
	}

	/**
	 * 初始化竞速游戏
	 */
	public static void initTimelessGame()
	{
		gameInfo.reset();
		gameInfo.setMode(GameMode.Timeless);
		gameInfo.setLevelInfo(LevelGenerator.rand());
		// 从数据库获取对应的数据
		UserInfo user = DatabaseOperator.getUserInfo();
		gameInfo.setHighScore(user.getTimelessHighScore());
		gameInfo.setNewRecord(false);
		gameInfo.setFindItemCount(user.getFindItemCount());
		gameInfo.setClockItemCount(user.getClockItemCount());
		// 根据模式设置游戏时间
		gameInfo.setTotalTime(GameStrategy.TIMELESS_GAME_BASE_TIME);
		GameScene.getInstance().startGame(gameInfo);
		gameInfo.setRunning(true);
	}

	/**
	 * 初始化快速游戏
	 */
	public static void initQuickGame()
	{
		gameInfo.reset();
		gameInfo.setMode(GameMode.QuickGame);
		gameInfo.setLevelInfo(LevelGenerator.rand());
		// 从数据库获取对应的数据
		UserInfo user = DatabaseOperator.getUserInfo();
		gameInfo.setHighScore(user.getQuickGameHighScore());
		gameInfo.setNewRecord(false);
		gameInfo.setFindItemCount(user.getFindItemCount());
		gameInfo.setClockItemCount(user.getClockItemCount());
		// 根据模式设置游戏时间
		gameInfo.setTotalTime(GameStrategy.QUICK_GAME_BASE_TIME);
		GameScene.getInstance().startGame(gameInfo);
		gameInfo.setRunning(true);
	}

	/**
	 * 根据游戏进度初始化游戏
	 * 
	 * @param archive
	 * @param mode
	 */
	public static void initGameByArchive(Archive archive, GameMode mode)
	{
		gameInfo.reset();
		// 根据进度初始化数据
		gameInfo.setCurScore(archive.getScore());
		gameInfo.setCurCombo(archive.getCurCombo());
		gameInfo.setMaxCombo(archive.getMaxCombo());
		gameInfo.setLevelCount(archive.getLevelCount());
		gameInfo.setClickCount(archive.getClickCount());
		gameInfo.setRightCount(archive.getRightCount());
		gameInfo.setMode(mode);
		// 根据进度设置关卡信息
		gameInfo.setLevelInfo(LevelGenerator.getByArchive(archive));
		// 从数据库获取对应的数据
		UserInfo user = DatabaseOperator.getUserInfo();
		int hiScore = mode == GameMode.QuickGame ? user.getQuickGameHighScore() : user.getTimelessHighScore();
		gameInfo.setHighScore(hiScore);
		gameInfo.setNewRecord(gameInfo.getCurScore() >= gameInfo.getHighScore());
		if (gameInfo.isNewRecord())
		{
			gameInfo.setHighScore(gameInfo.getCurScore());
		}
		gameInfo.setFindItemCount(user.getFindItemCount());
		gameInfo.setClockItemCount(user.getClockItemCount());
		// 根据模式设置游戏时间
		gameInfo.setTotalTime(archive.getRemainTime());
		GameScene.getInstance().startGame(gameInfo);
		gameInfo.setRunning(true);
	}

	/**
	 * 切换到下一个游戏场景，即切换地图
	 * 
	 * @param mode
	 */
	public static void switchToNextScene(final GameMode mode)
	{
		GameInfoBoard board = GameScene.getInstance().getGameBGLayer().getBoard();

		gameInfo.setMode(mode);
		gameInfo.setLevelCount(gameInfo.getLevelCount() + 1);
		gameInfo.setLevelInfo(LevelGenerator.rand());
		// 根据模式设置重新设置时间，并且根据进度，时间可以改变
		switch (mode)
		{
			case QuickGame:
				gameInfo.setTotalTime(Math.max(GameStrategy.QUICK_GAME_MIN_TIME, GameStrategy.QUICK_GAME_BASE_TIME
						- GameStrategy.QUICK_GAME_REDUCE_TIME * gameInfo.getLevelCount()));
				break;
			case Timeless:
				gameInfo.setTotalTime(board.getRemainTime());
				break;
		}
		GameScene.getInstance().getGameLayer().initMap(gameInfo);
		// 游戏相关信息的更新
		board.init(gameInfo);
		board.startTimer();
	}

	/**
	 * 时间到游戏结束
	 */
	public static void endGame()
	{
		gameInfo.setRunning(false);
		GameScene.getInstance().endGame();
		// 保存最高分和最高关卡
		UserInfo user = DatabaseOperator.getUserInfo();
		switch (gameInfo.getMode())
		{
			case QuickGame:
				if (gameInfo.getHighScore() > user.getQuickGameHighScore())
				{
					user.setQuickGameHighScore(gameInfo.getHighScore());
					WiGameUtil.submitScore(WiGameUtil.QUICKGAME_SCORE_LEADERBOARD_ID, gameInfo.getHighScore());
				}
				if (gameInfo.getLevelCount() > user.getQuickGameMaxLevel())
				{
					user.setQuickGameMaxLevel(gameInfo.getLevelCount());
					WiGameUtil.submitScore(WiGameUtil.QUICKGAME_LEVEL_LEADERBOARD_ID, gameInfo.getLevelCount());
				}
				break;
			case Timeless:
				if (gameInfo.getHighScore() > user.getTimelessHighScore())
				{
					user.setTimelessHighScore(gameInfo.getHighScore());
					WiGameUtil.submitScore(WiGameUtil.TIMELESS_SCORE_LEADERBOARD_ID, gameInfo.getHighScore());
				}
				if (gameInfo.getLevelCount() > user.getTimelessMaxLevel())
				{
					user.setTimelessMaxLevel(gameInfo.getLevelCount());
					WiGameUtil.submitScore(WiGameUtil.TIMELESS_LEVEL_LEADERBOARD_ID, gameInfo.getLevelCount());
				}
				break;
		}
		DatabaseOperator.saveUserInfo(user);
	}

	public static void retry()
	{
		switch (gameInfo.getMode())
		{
			case QuickGame:
				GameSystem.initQuickGame();
				break;
			case Timeless:
				GameSystem.initTimelessGame();
				break;
		}
	}

	/**
	 * 保存游戏进度
	 */
	public static void saveGameProgress()
	{
		// 游戏处于进行中才保存进度
		if (gameInfo.isRunning())
		{
			Archive archive = new Archive();
			archive.setRemainTime(GameScene.getInstance().getGameBGLayer().getBoard().getRemainTime());
			archive.setScore(gameInfo.getCurScore());
			archive.setCurCombo(gameInfo.getCurCombo());
			archive.setMaxCombo(gameInfo.getMaxCombo());
			archive.setLevelCount(gameInfo.getLevelCount());
			archive.setClickCount(gameInfo.getClickCount());
			archive.setRightCount(gameInfo.getRightCount());
			archive.setMapIndex(gameInfo.getLevelInfo().getImageIndex());
			archive.setPieces(gameInfo.getLevelInfo().getPiecesIndex());
			archive.setFoundPieces(GameScene.getInstance().getGameLayer().getPieces().getFoundPiecesIndex());
			switch (gameInfo.getMode())
			{
				case QuickGame:
					ArchiveHelper.saveQuickGameArchive(archive);
					break;
				case Timeless:
					ArchiveHelper.saveTimelessArchive(archive);
					break;
			}
			ArchiveHelper.setHasArchive(gameInfo.getMode(), true);
		}
	}

	/**
	 * 返回是否加载了游戏进度，没有则进入正常的游戏流程
	 * 
	 * @param mode
	 * @return
	 */
	public static boolean loadGameProgress(final GameMode mode)
	{
		if (ArchiveHelper.hasArchive(mode))
		{
			MainActivity.Instance.runOnUiThread(new Runnable()
			{
				@Override
				public void run()
				{
					AlertDialog alertDialog = new AlertDialog.Builder(MainActivity.Instance).setTitle("提示").setMessage("是否继续上次未完成的游戏")
							.setPositiveButton("继续游戏", new DialogInterface.OnClickListener()
							{
								public void onClick(DialogInterface dialog, int which)
								{
									Archive archive = null;
									// 载入进度继续
									switch (mode)
									{
										case QuickGame:
											archive = ArchiveHelper.getQuickGameArchive();
											break;
										case Timeless:
											archive = ArchiveHelper.getTimelessArchive();
											break;
									}
									if (archive != null)
									{
										GameUtil.switchScene(GameScene.make());
										GameSystem.initGameByArchive(archive, mode);
									}
								}
							}).setNegativeButton("重新开始", new DialogInterface.OnClickListener()
							{
								public void onClick(DialogInterface dialog, int which)
								{
									// 按照正常的流程继续
									GameUtil.switchScene(GameScene.make());
									switch (mode)
									{
										case QuickGame:
											GameSystem.initQuickGame();
											break;
										case Timeless:
											GameSystem.initTimelessGame();
											break;
									}
									return;
								}
							}).setCancelable(false).create(); // 创建对话框
					alertDialog.show();
				}
			});
			ArchiveHelper.setHasArchive(mode, false);
			return true;
		}
		return false;
	}

	public static void dispose()
	{
		AudioManager.stopBackgroundMusic();
		AudioManager.removeAllEffects();
		TextureManager.getInstance().removeAllTextures();
	}
}
