<?php

//include_once(module_load_include('inc', 'block', 'block.admin'));

/**
 * Form constructor.
 *
 * @see exchange_links_add_block_form_validate()
 * @see exchange_links_add_block_form_submit()
 */

function exchange_links_add_block_form($form, &$form_state) {
  include_once(module_load_include('inc', 'block', 'block.admin'));
  return block_admin_configure($form, $form_state, 'exchange_links', NULL);
}

/**
 * Form validator.
 *
 * @see exchange_links_add_block_form()
 * @see exchange_links_add_block_form_submit()
 */

function exchange_links_add_block_form_validate($form, &$form_state) {
  //dpm($form_state);
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

/**
 * Form submit.
 *
 * @see exchange_links_add_block_form_validate()
 * @see exchange_links_add_block_form()
 */

function exchange_links_add_block_form_submit($form, &$form_state) {
  //dpm($form_state['values']);
  $block_id = db_insert('exchange_links_blocks')
    ->fields(array(
      'service' => $form_state['values']['exchange_links_service'],
      'user' => $form_state['values']['exchange_links_user'],
      'debug' => $form_state['values']['exchange_links_debug'],
      'show_code' => $form_state['values']['exchange_links_show_code'],
    ))
    ->execute();
  $delta = exchange_links_delta($block_id);
  $query = db_insert('block')->fields(array('visibility', 'pages', 'custom', 'title', 'module', 'theme', 'status', 'weight', 'delta', 'cache'));
  foreach (list_themes() as $key => $theme) {
    if ($theme->status) {
      $query->values(array(
        'visibility' => (int) $form_state['values']['visibility'],
        'pages' => trim($form_state['values']['pages']),
        'custom' => (int) $form_state['values']['custom'],
        'title' => $form_state['values']['title'],
        'module' => $form_state['values']['module'],
        'theme' => $theme->name,
        'status' => 0,
        'weight' => 0,
        'delta' => $delta,
        'cache' => DRUPAL_NO_CACHE,
      ));
    }
  }
  $query->execute();

  $query = db_insert('block_role')->fields(array('rid', 'module', 'delta'));
  foreach (array_filter($form_state['values']['roles']) as $rid) {
    $query->values(array(
      'rid' => $rid,
      'module' => $form_state['values']['module'],
      'delta' => $delta,
    ));
  }
  $query->execute();

  // Store regions per theme for this block
  foreach ($form_state['values']['regions'] as $theme => $region) {
    db_merge('block')
      ->key(array('theme' => $theme, 'delta' => $delta, 'module' => $form_state['values']['module']))
      ->fields(array(
        'region' => ($region == BLOCK_REGION_NONE ? '' : $region),
        'pages' => trim($form_state['values']['pages']),
        'status' => (int) ($region != BLOCK_REGION_NONE),
      ))
      ->execute();
  }

  drupal_set_message(t('The block has been created.'));
  cache_clear_all();
  $form_state['redirect'] = 'admin/structure/block';
}


/**
 * Form delete block.
 *
 * @see exchange_links_delete_block_form_validate()
 * @see exchange_links_delete_block_form_submit()
 */

function exchange_links_delete_block_form($form, $form_state, $module, $info) {
//  include_once(module_load_include('inc', 'block', 'block.admin'));
//  return block_admin_configure($form, $form_state, 'exchange_links', NULL);
  return array();
}

