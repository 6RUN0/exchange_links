<?php

/**
 * Form constructor.
 *
 * @see exchange_links_add_block_form_validate()
 * @see exchange_links_add_block_form_submit()
 */

function exchange_links_add_block_form($form, &$form_state) {
  $form = array();
  $form = exchange_links_block_configure();
  $form['exchange_links_submit'] = array(
    '#type' => 'submit',
    '#name' => 'save',
    '#value' => t('Add block'),
  );
  return $form;
}

/**
 * Form validator.
 *
 * @see exchange_links_add_block_form()
 * @see exchange_links_add_block_form_submit()
 */

function exchange_links_add_block_form_validate($form, $form_state) {
  //dpm($form_state);
  if($form_state['clicked_button']['#name'] == 'save') {
    $block_exist = db_select('exchange_links_blocks', 'blocks')
      ->fields('blocks')
      ->condition('service', $form_state['values']['exchange_links_service'], '=')
      ->condition('user', $form_state['values']['exchange_links_user'], '=')
      ->execute()
      ->fetchField();
    if($block_exist) {
      form_set_error('exchange_links_service');
      form_set_error('exchange_links_user', t('block exist'));
    }
  }
}

/**
 * Form submit.
 *
 * @see exchange_links_add_block_form_validate()
 * @see exchange_links_add_block_form()
 */

function exchange_links_add_block_form_submit($form, &$form_state) {
  //dpm($form_state['values']);
  if($form_state['clicked_button']['#name'] == 'save') {
    $block_id = db_insert('exchange_links_blocks')
      ->fields(array(
        'service' => $form_state['values']['exchange_links_service'],
        'user' => $form_state['values']['exchange_links_user'],
        'debug' => $form_state['values']['exchange_links_debug'],
        'show_code' => $form_state['values']['exchange_links_show_code'],
      ))
      ->execute();
    $delta = exchange_links_delta($block_id);
    drupal_set_message(t('The block has been created.'));
    cache_clear_all();
    $form_state['redirect'] = "admin/structure/block/manage/exchange_links/$delta/configure";
  }
}

function exchange_links_del_block_form($form, &$form_state, $delta) {
  $form = array();
  return $form;
}
