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
  foreach($form['blocks'] as $key => $block) {
    if($block['module']['#value'] == 'exchange_links') {
      $form['blocks'][$key]['delete'] = array(
        '#type' => 'link',
        '#title' => t('delete'),
        '#href' => 'admin/structure/block/manage/exchange_links/' . $block['delta']['#value'] . '/delete',
      );
    }
  }
  //dpm($form);
}
