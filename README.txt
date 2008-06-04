; $Id$

The RealName module allows the admin to choose fields from the user profile
that will be used to add a "realname" element (method) to a user object.
Hook_user is used to automatically add this to any user object that is loaded.

Installation
------------
Standard module installation applies.

Menus
-----
The only menu item is for the settings page.

Settings
--------
The settings page is at Administer >> User >> Realname.

This is where you choose which fields from the profile will be used
to create the user's RealName.

Note: Currently only "single line textfield" data will be shown.

The "Separator" value will be placed between the pieces of the name.

TODO: Change to a pattern for more flexilibility.

Permissions
-----------
There are no new permissions. The settings page is controlled by the
"administer users" permission.