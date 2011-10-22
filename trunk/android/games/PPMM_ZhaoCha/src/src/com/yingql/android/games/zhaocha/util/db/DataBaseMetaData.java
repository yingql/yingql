package com.yingql.android.games.zhaocha.util.db;

public class DataBaseMetaData
{
	public static final String DATABASE_NAME = "zhaochaDB";
	public static final String USERINFO_TABLE_NAME = "UserInfo";

	public static final class UserInfoTableMetaData
	{
		public static final String ID = "id";
		public static final String Name = "name";
		public static final String Coins = "coins";
		public static final String IsMusicOn = "isMusicOn";
		public static final String QuickGameHighScore = "quickGameHighScore";
		public static final String TimelessHighScore = "timelessHighScore";
		public static final String QuickGameMaxLevel = "quickGameMaxLevel";
		public static final String TimelessMaxLevel = "timelessMaxLevel";
		public static final String FindItemCount = "findItemCount";
		public static final String ClockItemCount = "clockItemCount";

		public static String getCreateSql()
		{
			String sql = String
					.format("create table %s (%s INTEGER PRIMARY KEY AUTOINCREMENT , %s varchar(50), %s INTEGER, %s INTEGER, %s INTEGER , %s INTEGER, %s INTEGER, %s INTEGER, %s INTEGER , %s INTEGER);",
							USERINFO_TABLE_NAME, ID, Name, Coins, IsMusicOn, QuickGameHighScore, TimelessHighScore, QuickGameMaxLevel,
							TimelessMaxLevel, FindItemCount, ClockItemCount);
			return sql;
		}
	}
}
