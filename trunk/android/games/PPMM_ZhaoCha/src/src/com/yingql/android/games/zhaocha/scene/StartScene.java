package com.yingql.android.games.zhaocha.scene;

import android.view.KeyEvent;

import com.wiyun.engine.nodes.Scene;
import com.yingql.android.games.zhaocha.MainActivity;
import com.yingql.android.games.zhaocha.layer.GameHelperLayer;
import com.yingql.android.games.zhaocha.layer.StartMenuLayer;

public class StartScene extends Scene
{
	private static StartScene scene = null;
	private static Object syncObj = new Object();
	private StartMenuLayer layer;
	private GameHelperLayer gameHelperLayer;

	protected StartScene()
	{
		gameHelperLayer = new GameHelperLayer();
		layer = new StartMenuLayer();
		this.addChild(layer, 1);
		this.addChild(gameHelperLayer, 2);
		gameHelperLayer.setVisible(false);
	}

	public static StartScene getInstance()
	{
		return make();
	}

	public static StartScene make()
	{
		if (scene == null)
		{
			synchronized (syncObj)
			{
				if (scene == null)
				{
					scene = new StartScene();
					scene.autoRelease(true);
				}
			}
		}
		return scene;
	}

	public void init()
	{
		this.layer.init();
	}

	public void showHelp()
	{
		this.layer.setTouchEnabled(false);
		this.gameHelperLayer.setVisible(true);
	}

	public void closeHelp()
	{
		this.layer.setTouchEnabled(true);
		this.gameHelperLayer.setVisible(false);
	}

	@Override
	public boolean wyKeyDown(KeyEvent event)
	{
		if (event.getKeyCode() == KeyEvent.KEYCODE_BACK)
		{
			if (this.gameHelperLayer.isVisible())
			{
				this.closeHelp();
			}
			else
			{
				MainActivity.Instance.showExitTips();
			}
			return true;
		}
		return super.wyKeyDown(event);
	}
}
