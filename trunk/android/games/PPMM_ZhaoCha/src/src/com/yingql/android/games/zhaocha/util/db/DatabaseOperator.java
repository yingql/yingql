package com.yingql.android.games.zhaocha.util.db;

import android.content.ContentValues;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;

import com.yingql.android.games.zhaocha.MainActivity;
import com.yingql.android.games.zhaocha.entity.UserInfo;

/**
 * @author yingql
 * 
 */
public class DatabaseOperator
{
	private static UserInfo userInfo;

	/**
	 * 获取用户信息
	 * 
	 * @return
	 */
	public static UserInfo getUserInfo()
	{
		if (DatabaseOperator.userInfo == null)
		{
			UserInfo info = new UserInfo();
			DatabaseHelper helper = new DatabaseHelper(MainActivity.Instance, DataBaseMetaData.DATABASE_NAME);
			SQLiteDatabase db = helper.getReadableDatabase();
			Cursor cs = db.query(DataBaseMetaData.USERINFO_TABLE_NAME, new String[] { DataBaseMetaData.UserInfoTableMetaData.ID,
					DataBaseMetaData.UserInfoTableMetaData.Name, DataBaseMetaData.UserInfoTableMetaData.Coins,
					DataBaseMetaData.UserInfoTableMetaData.QuickGameHighScore, DataBaseMetaData.UserInfoTableMetaData.QuickGameMaxLevel,
					DataBaseMetaData.UserInfoTableMetaData.TimelessHighScore, DataBaseMetaData.UserInfoTableMetaData.TimelessMaxLevel,
					DataBaseMetaData.UserInfoTableMetaData.IsMusicOn, DataBaseMetaData.UserInfoTableMetaData.ClockItemCount,
					DataBaseMetaData.UserInfoTableMetaData.FindItemCount }, null, null, null, null, null);
			while (cs.moveToNext())
			{
				info.setId(cs.getInt(cs.getColumnIndex(DataBaseMetaData.UserInfoTableMetaData.ID)));
				info.setUserName(cs.getString(cs.getColumnIndex(DataBaseMetaData.UserInfoTableMetaData.Name)));
				info.setCoins(cs.getInt(cs.getColumnIndex(DataBaseMetaData.UserInfoTableMetaData.Coins)));
				info.setMusicOn(cs.getInt(cs.getColumnIndex(DataBaseMetaData.UserInfoTableMetaData.IsMusicOn)) != 0);
				info.setClockItemCount(cs.getInt(cs.getColumnIndex(DataBaseMetaData.UserInfoTableMetaData.ClockItemCount)));
				info.setFindItemCount(cs.getInt(cs.getColumnIndex(DataBaseMetaData.UserInfoTableMetaData.FindItemCount)));
				info.setQuickGameHighScore(cs.getInt(cs.getColumnIndex(DataBaseMetaData.UserInfoTableMetaData.QuickGameHighScore)));
				info.setQuickGameMaxLevel(cs.getInt(cs.getColumnIndex(DataBaseMetaData.UserInfoTableMetaData.QuickGameMaxLevel)));
				info.setTimelessHighScore(cs.getInt(cs.getColumnIndex(DataBaseMetaData.UserInfoTableMetaData.TimelessHighScore)));
				info.setTimelessMaxLevel(cs.getInt(cs.getColumnIndex(DataBaseMetaData.UserInfoTableMetaData.TimelessMaxLevel)));
				break;
			}
			cs.close();
			if (db.isOpen())
				db.close();
			DatabaseOperator.userInfo = info;
		}
		return DatabaseOperator.userInfo;
	}

	/**
	 * 保存用户信息
	 * 
	 * @param db
	 * @param userInfo
	 */
	public static void saveUserInfo(SQLiteDatabase db, UserInfo userInfo)
	{
		if (userInfo != null)
		{
			ContentValues values = new ContentValues();
			values.put(DataBaseMetaData.UserInfoTableMetaData.Name, userInfo.getUserName());
			values.put(DataBaseMetaData.UserInfoTableMetaData.Coins, userInfo.getCoins());
			values.put(DataBaseMetaData.UserInfoTableMetaData.IsMusicOn, userInfo.isMusicOn() ? 1 : 0);
			values.put(DataBaseMetaData.UserInfoTableMetaData.QuickGameHighScore, userInfo.getQuickGameHighScore());
			values.put(DataBaseMetaData.UserInfoTableMetaData.QuickGameMaxLevel, userInfo.getQuickGameMaxLevel());
			values.put(DataBaseMetaData.UserInfoTableMetaData.TimelessHighScore, userInfo.getTimelessHighScore());
			values.put(DataBaseMetaData.UserInfoTableMetaData.TimelessMaxLevel, userInfo.getTimelessMaxLevel());
			values.put(DataBaseMetaData.UserInfoTableMetaData.ClockItemCount, userInfo.getClockItemCount());
			values.put(DataBaseMetaData.UserInfoTableMetaData.FindItemCount, userInfo.getFindItemCount());
			if (userInfo.getId() >= 0)
			{
				db.update(DataBaseMetaData.USERINFO_TABLE_NAME, values, null, null);
			}
			else
			{
				db.insert(DataBaseMetaData.USERINFO_TABLE_NAME, null, values);
			}
			DatabaseOperator.userInfo = userInfo;
		}
	}

	/**
	 * 保存用户信息
	 * 
	 * @param userInfo
	 * 
	 */
	public static void saveUserInfo(UserInfo userInfo)
	{
		if (userInfo != null)
		{
			DatabaseHelper helper = new DatabaseHelper(MainActivity.Instance, DataBaseMetaData.DATABASE_NAME);
			SQLiteDatabase db = helper.getWritableDatabase();
			saveUserInfo(db, userInfo);
			if (db.isOpen())
				db.close();
		}
	}
}
