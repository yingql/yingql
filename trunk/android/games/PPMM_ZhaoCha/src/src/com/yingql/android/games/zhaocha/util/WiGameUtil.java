package com.yingql.android.games.zhaocha.util;

import android.content.Context;

import com.wiyun.game.WiGame;
import com.wiyun.game.WiGameClient;

/**
 * 微云游戏平台相关帮助类
 * 
 * @author yingql
 * 
 */
public class WiGameUtil
{
	public static final String APP_KEY = "0cf6351f624d0002";

	public static final String SECRET_KEY = "2khgCWaG8khrkv5mgF2P6pxWpesPTFTK";
	/**
	 * 快速模式分数排行
	 */
	public static final String QUICKGAME_SCORE_LEADERBOARD_ID = "c491f37e026e43e4 ";
	/**
	 * 快速模式闯关数排行
	 */
	public static final String QUICKGAME_LEVEL_LEADERBOARD_ID = "d9a48046add2f2d3 ";
	/**
	 * 尽速模式分数排行
	 */
	public static final String TIMELESS_SCORE_LEADERBOARD_ID = "77e28ac123382270 ";
	/**
	 * 尽速模式闯关数排行
	 */
	public static final String TIMELESS_LEVEL_LEADERBOARD_ID = "9e8914308e40391f ";

	/**
	 * 初始化微云平台
	 * 
	 * @param context
	 */
	public static void init(Context context)
	{
		initWiGame(context);		
	}

	/**
	 * 初始化微云游戏
	 * 
	 * @param context
	 */
	private static void initWiGame(Context context)
	{
		WiGame.init(context, APP_KEY, SECRET_KEY, "1.0", false, false);
		WiGame.setToastSide(WiGame.TOAST_SIDE_BOTTOM);
		WiGame.addWiGameClient(mClient);
	}

	// 所有的回调都是在UI线程中发生的，如果您需要做一些时间比较长的操作，请在线程中进行
	private static WiGameClient mClient = new WiGameClient()
	{
	};

	/**
	 * 提交排行榜分数
	 * 
	 * @param id
	 * @param score
	 */
	public static void submitScore(String id, int score)
	{
		WiGame.submitScore(id, score, null, true);
	}

	/**
	 * 任意模式连击数成就
	 * 
	 * @author yingql
	 * 
	 */
	public static class ComboAchievement
	{
		/**
		 * 蜗行牛步
		 */
		public static final String COMBO_5 = "81bb325c022837e8";
		/**
		 * 不疾不徐
		 */
		public static final String COMBO_10 = "a22f1ca399387113";
		/**
		 * 眼疾手快
		 */
		public static final String COMBO_25 = "4032753529f7d2c8";
		/**
		 * 奔逸绝尘
		 */
		public static final String COMBO_40 = "443f36ba3ca421db";
		/**
		 * 风驰电掣
		 */
		public static final String COMBO_50 = "9570ade92f66b977";
		/**
		 * 一日千里
		 */
		public static final String COMBO_70 = "413ccf14943ae7e7";

		/**
		 * 解锁成就
		 * 
		 * @param combo
		 */
		public static void unlockComboAchievement(int combo)
		{
			if (combo >= 5)
			{
				WiGame.unlockAchievement(COMBO_5);
			}
			if (combo >= 10)
			{
				WiGame.unlockAchievement(COMBO_10);
			}
			if (combo >= 25)
			{
				WiGame.unlockAchievement(COMBO_25);
			}
			if (combo >= 40)
			{
				WiGame.unlockAchievement(COMBO_40);
			}
			if (combo >= 50)
			{
				WiGame.unlockAchievement(COMBO_50);
			}
			if (combo >= 70)
			{
				WiGame.unlockAchievement(COMBO_70);
			}
		}
	}

	/**
	 * 
	 * 任意模式分数成就
	 * 
	 * @author yingql
	 * 
	 */
	public static class ScoreAchievement
	{
		/**
		 * 初出江湖
		 */
		public static final String SCORE_500 = "ef6547182815f2bd";
		/**
		 * 颇具潜力
		 */
		public static final String SCORE_1000 = "6d38f8ca1ef1f3d8";
		/**
		 * 初显锋芒
		 */
		public static final String SCORE_2000 = "c7dc678d17af2460";
		/**
		 * 声名显赫
		 */
		public static final String SCORE_5000 = "9fe6b5613d8acbbf";
		/**
		 * 万人景仰
		 */
		public static final String SCORE_10000 = "360146f2adbc602f";
		/**
		 * 天下无双
		 */
		public static final String SCORE_20000 = "766f1263a01786a9";

		/**
		 * 解锁成就
		 * 
		 * @param score
		 */
		public static void unlockScoreAchievement(int score)
		{
			if (score >= 500)
			{
				WiGame.unlockAchievement(SCORE_500);
			}
			if (score >= 1000)
			{
				WiGame.unlockAchievement(SCORE_1000);
			}
			if (score >= 2000)
			{
				WiGame.unlockAchievement(SCORE_2000);
			}
			if (score >= 5000)
			{
				WiGame.unlockAchievement(SCORE_5000);
			}
			if (score >= 10000)
			{
				WiGame.unlockAchievement(SCORE_10000);
			}
			if (score >= 20000)
			{
				WiGame.unlockAchievement(SCORE_20000);
			}
		}
	}
}
