package com.yingql.android.games.zhaocha;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.WindowManager;
import android.widget.Toast;

import com.admogo.AdMogoManager;
import com.mobclick.android.MobclickAgent;
import com.wiyun.engine.nodes.Director;
import com.wiyun.engine.nodes.Director.IDirectorLifecycleListener;
import com.wiyun.engine.opengl.WYGLSurfaceView;
import com.wiyun.game.WiGame;
import com.yingql.android.games.zhaocha.core.GameSystem;
import com.yingql.android.games.zhaocha.scene.GameLoadingScene;
import com.yingql.android.games.zhaocha.util.ADHelper;

public class MainActivity extends Activity implements IDirectorLifecycleListener
{
	protected WYGLSurfaceView mGLSurfaceView;
	private boolean mStarted;
	public static MainActivity Instance;

	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		Instance = this;
		//MobclickAgent.onError(this);
		mGLSurfaceView = new WYGLSurfaceView(this);
		setContentView(mGLSurfaceView);
		Director.getInstance().addLifecycleListener(this);		
		Director.setDefaultInDensity(1.5f);
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON, WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
	}

	@Override
	protected void onPause()
	{
		super.onPause();
		MobclickAgent.onPause(this);
		GameSystem.saveGameProgress();
		Director.getInstance().pause();
	}

	@Override
	protected void onResume()
	{
		super.onResume();
		MobclickAgent.onResume(this);
		Director.getInstance().resume();
	}

	@Override
	protected void onDestroy()
	{
		AdMogoManager.clear();
		WiGame.destroy(this);
		GameSystem.dispose();
		Director.getInstance().end();
		super.onDestroy();
		android.os.Process.killProcess(android.os.Process.myPid());
	}

	@Override
	public boolean dispatchKeyEvent(KeyEvent event)
	{
		if (event.getKeyCode() == KeyEvent.KEYCODE_BACK)
		{
			return mGLSurfaceView.dispatchKeyEvent(event);
		}

		else
			return super.dispatchKeyEvent(event);
	}

	public void onDirectorPaused()
	{
	}

	public void onDirectorResumed()
	{
	}

	public void onDirectorEnded()
	{
	}

	public void onDirectorScreenCaptured(String path)
	{
	}

	public void onSurfaceChanged(final int w, final int h)
	{
		if (!mStarted)
		{
			mStarted = true;
			if (w > h)
			{
				GameSystem.Screen_Width = w;
				GameSystem.Screen_Height = h;
			}
			else
			{
				GameSystem.Screen_Width = h;
				GameSystem.Screen_Height = w;
			}			
			Director.getInstance().runWithScene(GameLoadingScene.make());			
			ADHelper.initAD();
		}
	}

	public void onSurfaceCreated()
	{
	}

	public void onSurfaceDestroyed()
	{
	}

	public void showExitTips()
	{
		runOnUiThread(new Runnable()
		{
			@Override
			public void run()
			{
				AlertDialog alertDialog = new AlertDialog.Builder(MainActivity.this).setTitle("退出程序").setMessage("是否退出程序")
						.setPositiveButton("确定", new DialogInterface.OnClickListener()
						{
							public void onClick(DialogInterface dialog, int which)
							{
								MainActivity.this.finish();
								AdMogoManager.clear();
								WiGame.destroy(MainActivity.this);
								GameSystem.dispose();
								Director.getInstance().end();
								android.os.Process.killProcess(android.os.Process.myPid());
							}
						}).setNegativeButton("取消", new DialogInterface.OnClickListener()
						{
							public void onClick(DialogInterface dialog, int which)
							{
								return;
							}
						}).setCancelable(false).create(); // 创建对话框
				alertDialog.show();
			}
		});
	}

	public void showTip(final String tip)
	{
		runOnUiThread(new Runnable()
		{
			@Override
			public void run()
			{
				Toast.makeText(MainActivity.this, tip, Toast.LENGTH_LONG).show();
			}
		});
	}
}