package com.yingql.android.games.zhaocha.util;

import java.io.Closeable;
import java.io.IOException;
import java.util.Random;

import com.wiyun.engine.nodes.Director;
import com.wiyun.engine.nodes.Scene;
import com.wiyun.engine.transitions.ColorFadeTransition;
import com.wiyun.engine.types.WYColor3B;
import com.yingql.android.games.zhaocha.MainActivity;

public class GameUtil
{
	public static String EVENT_CLICK_AD = "clickAd";
	public static String EVENT_BUY_FIND = "buyFind";
	public static String EVENT_BUY_CLOCK = "buyClock";
	
	private static Random rand = new Random();

	public static Random getRand()
	{
		return rand;
	}

	public static int getResId(String resName)
	{
		return MainActivity.Instance.getResources().getIdentifier(resName, "drawable", MainActivity.Instance.getPackageName());
	}

	/**
	 * 关闭流
	 * 
	 * @param stream
	 */
	public static void closeStream(Closeable stream)
	{
		if (stream != null)
		{
			try
			{
				stream.close();
			}
			catch (IOException e)
			{
			}
		}
	}

	/**
	 * 转换游戏场景
	 * 
	 * @param toScene
	 */
	public static void switchScene(Scene toScene)
	{
		Scene scene = ColorFadeTransition.make(0.3f, toScene, WYColor3B.make(0, 0, 0));
		// TODO 注意内存问题
		// scene.autoRelease();
		Director.getInstance().replaceScene(scene);
	}
}
