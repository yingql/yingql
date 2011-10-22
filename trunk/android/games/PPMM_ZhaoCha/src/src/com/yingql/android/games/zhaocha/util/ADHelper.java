package com.yingql.android.games.zhaocha.util;

import android.view.Gravity;
import android.view.View;
import android.widget.FrameLayout;

import com.admogo.AdMogoLayout;
import com.admogo.AdMogoListener;
import com.mobclick.android.MobclickAgent;
import com.wiyun.engine.utils.ResolutionIndependent;
import com.yingql.android.games.zhaocha.MainActivity;
import com.yingql.android.games.zhaocha.core.GameStrategy;
import com.yingql.android.games.zhaocha.entity.UserInfo;
import com.yingql.android.games.zhaocha.scene.GameScene;
import com.yingql.android.games.zhaocha.util.db.DatabaseOperator;

public class ADHelper implements AdMogoListener
{
	private static final String mogoID = "84015b7a7f584fe28130e4af670d99f5";
	private static ADHelper Instance = new ADHelper();
	private static AdMogoLayout adMogoLayoutCode;

	private ADHelper()
	{
	}

	/**
	 * 初始化味千广告
	 * 
	 */
	public static void initAD()
	{
		MainActivity.Instance.runOnUiThread(new Runnable()
		{
			@Override
			public void run()
			{
				adMogoLayoutCode = new AdMogoLayout(MainActivity.Instance, mogoID);
				FrameLayout.LayoutParams params = new FrameLayout.LayoutParams(FrameLayout.LayoutParams.FILL_PARENT, (int) ResolutionIndependent
						.resolveDp(50));
				// 设置广告出现的位置(悬浮于底部)
				params.gravity = Gravity.BOTTOM;
				params.bottomMargin = 0;
				params.leftMargin = 0;
				// 添加广告状态监听
				adMogoLayoutCode.setAdMogoListener(ADHelper.Instance);
				MainActivity.Instance.addContentView(adMogoLayoutCode, params);
				hideAd();
			}
		});
	}

	public static void showAd()
	{
		if (adMogoLayoutCode != null)
		{
			MainActivity.Instance.runOnUiThread(new Runnable()
			{
				@Override
				public void run()
				{
					adMogoLayoutCode.setVisibility(View.VISIBLE);
				}
			});
		}
	}

	public static void hideAd()
	{
		if (adMogoLayoutCode != null)
		{
			MainActivity.Instance.runOnUiThread(new Runnable()
			{
				@Override
				public void run()
				{
					adMogoLayoutCode.setVisibility(View.INVISIBLE);
				}
			});
		}
	}

	@Override
	public void onClickAd()
	{
		// 点击广告奖励金币，并且更新界面
		UserInfo user = DatabaseOperator.getUserInfo();
		user.setCoins(user.getCoins() + GameStrategy.CLICK_AD_REWARD);
		DatabaseOperator.saveUserInfo(user);
		GameScene.getInstance().updateCoins(user.getCoins());
		MobclickAgent.onEvent(MainActivity.Instance, GameUtil.EVENT_CLICK_AD);
	}

	@Override
	public void onFailedReceiveAd()
	{
	}

	@Override
	public void onReceiveAd()
	{
	}
}
