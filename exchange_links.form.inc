<?php

/**
 * Implements hook_form_alter()
 * @see exchange_links_hook_info_alter()
 */
function exchange_links_form_alter($form, $form_state) {
}

/**
 * Implements hook_form_FORM_ID_alter()
 * place form admin/structure/block
 */
function exchange_links_form_block_admin_display_form_alter(&$form, $form_state) {
  $result = db_select('exchange_links_blocks', 'blocks')
    ->fields('blocks')
    ->execute();
  while($record = $result->fetchObject()) {
    $form['blocks']["exchange_links_$record->bid"]['delete'] = array(
      '#type' => 'link',
      '#title' => t('delete'),
      '#href' => "admin/structure/block/manage/exchange_links/$record->bid/delete",
    );
  }
}
