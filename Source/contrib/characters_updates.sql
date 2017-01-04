UPDATE `updates` SET `state`='ARCHIVED';
DELETE FROM `character_aura` WHERE `itemGuid` != 0;
ALTER TABLE `character_aura` DROP COLUMN `itemGuid`;
