package com.yingql.android.games.zhaocha.sprite;

import com.yingql.android.games.zhaocha.R;
import com.yingql.android.games.zhaocha.core.GameStrategy;
import com.yingql.android.games.zhaocha.core.GameSystem;
import com.yingql.android.games.zhaocha.entity.GameInfo;
import com.yingql.android.games.zhaocha.entity.GameMode;
import com.yingql.android.games.zhaocha.entity.UserInfo;
import com.yingql.android.games.zhaocha.scene.GameScene;
import com.yingql.android.games.zhaocha.util.db.DatabaseOperator;

public class ClockItemButton extends ItemButton
{
	public ClockItemButton(GameInfoBoard board)
	{
		super(board);
	}

	@Override
	public void useItem()
	{
		if (this.board.isTouchEnabled())
		{
			// 判断是否能使用道具，不能使用则弹出道具购买界面
			if (this.count > 0)
			{
				this.setCount(this.count - 1);
				UserInfo user = DatabaseOperator.getUserInfo();
				user.setClockItemCount(this.count);
				DatabaseOperator.saveUserInfo(user);
				GameInfo info = GameSystem.getGameInfo();
				info.setClockItemCount(this.count);
				// 使用时间道具
				int maxTime = info.getMode() == GameMode.QuickGame ? GameStrategy.QUICK_GAME_BASE_TIME : GameStrategy.TIMELESS_GAME_BASE_TIME;
				this.board.setRemainTime(Math.min(maxTime, board.getRemainTime() + GameStrategy.CLOCK_ADD_TIME));
				GameSystem.playEffect(R.raw.clock);
			}
			else
			{
				buyItem();
			}
		}
	}

	@Override
	public void buyItem()
	{
		if (this.board.isTouchEnabled())
		{
			GameScene.getInstance().showBuyClockItemLayer();
		}
	}

	@Override
	public int getBgId()
	{
		return R.drawable.item_clock;
	}
}
