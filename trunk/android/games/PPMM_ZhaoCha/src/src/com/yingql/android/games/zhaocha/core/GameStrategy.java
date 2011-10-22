package com.yingql.android.games.zhaocha.core;

import com.yingql.android.games.zhaocha.R;
import com.yingql.android.games.zhaocha.entity.GameInfo;
import com.yingql.android.games.zhaocha.entity.GameMode;
import com.yingql.android.games.zhaocha.scene.GameScene;
import com.yingql.android.games.zhaocha.sprite.GameInfoBoard;

public class GameStrategy
{
	public static final int BASE_SCORE = 5;
	public static final int ERROR_CLICK_TIME = 5;
	public static final int QUICK_GAME_BASE_TIME = 90;
	public static final int QUICK_GAME_MIN_TIME = 10;
	public static final int QUICK_GAME_REDUCE_TIME = 5;
	public static final int TIMELESS_GAME_BASE_TIME = 120;
	public static final int CLOCK_ADD_TIME = 10;
	public static final float ALARM_TIME = 5;
	public static final int CLICK_AD_REWARD = 200;

	/**
	 * 点击茬，根据传入的参数判断这次点击是否找到
	 * 
	 * @param isFind
	 */
	public static void clickPiece(boolean isFind)
	{
		GameInfo info = GameSystem.getGameInfo();
		GameInfoBoard board = GameScene.getInstance().getGameBGLayer().getBoard();
		info.click(isFind);
		if (isFind)
		{
			info.combo();
			info.addScore(BASE_SCORE * info.getCurCombo());
			board.update(info);
			GameSystem.playEffect(R.raw.right);
			if (GameScene.getInstance().getGameLayer().getPieces().getRemainPieceCount() == 0)
			{
				// 处理全部都找到后结束游戏
				processEndOfOneScene(true);
			}
		}
		else
		{
			info.setCurCombo(0);
			board.update(info);
			// 点击错误，扣除时间
			board.setRemainTime(Math.max(0, board.getRemainTime() - ERROR_CLICK_TIME));
			GameSystem.playEffect(R.raw.wrong);
		}
	}

	/**
	 * 
	 * 使用道具随机找出一个茬
	 * 
	 * @return 是否找到了
	 */
	public static boolean findRandomPieceByItem()
	{
		GameInfo info = GameSystem.getGameInfo();
		GameInfoBoard board = GameScene.getInstance().getGameBGLayer().getBoard();
		boolean isFind = GameScene.getInstance().getGameLayer().getPieces().findRandomPiece();
		if (isFind)
		{
			// 使用道具会清空连击
			info.setCurCombo(1);
			info.addScore(BASE_SCORE * info.getCurCombo());
			board.update(info);
			GameSystem.playEffect(R.raw.right);
			if (GameScene.getInstance().getGameLayer().getPieces().getRemainPieceCount() == 0)
			{
				// 处理全部都找到后结束游戏
				processEndOfOneScene(true);
			}
		}
		return isFind;
	}

	/**
	 * 处理一个游戏场景结束，接下来根据不同的游戏模式和游戏进度进行相应的处理
	 * 
	 * @param isSuccess
	 *            这一场景是否成功
	 */
	public static void processEndOfOneScene(boolean isSuccess)
	{
		// 游戏结束时，如果还有剩余的时间，按照一定的比例计算到分数中去
		final GameInfo info = GameSystem.getGameInfo();
		GameInfoBoard board = GameScene.getInstance().getGameBGLayer().getBoard();
		board.stopTimer();
		switch (info.getMode())
		{
			case QuickGame:
			case Timeless:
				// 如果全部找完了，而不是时间到则切换到下一地图
				if (isSuccess)
				{
					info.addScore(BASE_SCORE * (int) board.getRemainTime());
					board.update(info);
					// TODO 暂时先停顿1秒后再切换场景，后期可以替换成pass动画等
					new Thread(new Runnable()
					{
						@Override
						public void run()
						{
							try
							{
								Thread.sleep(1000);
							}
							catch (InterruptedException e)
							{
								e.printStackTrace();
							}
							GameSystem.switchToNextScene(info.getMode());
						}
					}).start();
				}
				break;
		}
	}

	/**
	 * 计算评级
	 * 
	 * @param score
	 * @param maxCombo
	 * @param rate
	 * @return
	 */
	public static int calcRanks(int score, int maxCombo, float rate, GameMode mode)
	{
		int rank1 = 0, rank2 = 0, rank3 = 0;
		switch (mode)
		{
			case Timeless:
				if (score <= 100)
					rank1 = 0;
				else if (score <= 1000)
					rank1 = 1;
				else if (score <= 2000)
					rank1 = 2;
				else if (score <= 5000)
					rank1 = 3;
				else
					rank1 = 4;
				break;
			case QuickGame:				
			default:
				if (score <= 100)
					rank1 = 0;
				else if (score <= 1000)
					rank1 = 1;
				else if (score <= 2000)
					rank1 = 2;
				else if (score <= 10000)
					rank1 = 3;
				else
					rank1 = 4;
				break;
		}		

		if (maxCombo <= 5)
			rank2 = 0;
		else if (maxCombo <= 15)
			rank2 = 1;
		else if (maxCombo <= 35)
			rank2 = 2;
		else if (maxCombo <= 50)
			rank2 = 3;
		else
			rank2 = 4;

		if (rate <= 60)
			rank3 = 0;
		else if (rate <= 70)
			rank3 = 1;
		else if (rate <= 80)
			rank3 = 2;
		else if (rate <= 90)
			rank3 = 3;
		else
			rank3 = 4;
		return rank1 + rank2 + rank3;
	}
}