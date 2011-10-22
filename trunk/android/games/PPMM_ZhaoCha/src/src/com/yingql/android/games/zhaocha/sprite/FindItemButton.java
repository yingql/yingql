package com.yingql.android.games.zhaocha.sprite;

import com.yingql.android.games.zhaocha.R;
import com.yingql.android.games.zhaocha.core.GameStrategy;
import com.yingql.android.games.zhaocha.core.GameSystem;
import com.yingql.android.games.zhaocha.entity.UserInfo;
import com.yingql.android.games.zhaocha.scene.GameScene;
import com.yingql.android.games.zhaocha.util.db.DatabaseOperator;

public class FindItemButton extends ItemButton
{
	public FindItemButton(GameInfoBoard board)
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
				boolean isFind = GameStrategy.findRandomPieceByItem();
				// 更新道具数量
				if (isFind)
				{
					this.setCount(this.count - 1);
					UserInfo user = DatabaseOperator.getUserInfo();
					user.setFindItemCount(this.count);
					DatabaseOperator.saveUserInfo(user);
					GameSystem.getGameInfo().setFindItemCount(this.count);
				}
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
			GameScene.getInstance().showBuyFindItemLayer();			
		}
	}

	@Override
	public int getBgId()
	{
		return R.drawable.item_find;
	}
}
