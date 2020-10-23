	SECTION_PROLOGUE(__wh_app__section,,)
	{
		__wh_app_start = .;
		KEEP(*(SORT(*__wh_app__*)));
		__wh_app_end = .;
	} GROUP_LINK_IN(ROMABLE_REGION)