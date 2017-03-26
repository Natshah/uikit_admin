<?php

/**
 * @file
 * Process theme data for uikit_admin.
 */

/**
 * Load UIkit Admin's include files for theme processing.
 */
uikit_load_include('inc', 'uikit_admin', 'preprocess', 'includes');
uikit_load_include('inc', 'uikit_admin', 'process', 'includes');
uikit_load_include('inc', 'uikit_admin', 'theme', 'includes');
uikit_load_include('inc', 'uikit_admin', 'alter', 'includes');

/**
 * Returns a renderable array for the on-page link to add or remove a shortcut.
 */
function _uikit_admin_shortcut_add_or_remove_link() {
  uikit_get_cdn_asset('tooltip');
  $link = current_path();
  $query_parameters = drupal_get_query_parameters();

  if (!empty($query_parameters)) {
    $link .= '?' . drupal_http_build_query($query_parameters);
  }

  $query = array(
    'link' => $link,
    'name' => drupal_get_title(),
  );

  $query += drupal_get_destination();
  $shortcut_set = shortcut_current_displayed_set();

  // Check if $link is already a shortcut and set $link_mode accordingly.
  foreach ($shortcut_set->links as $shortcut) {
    if ($link == $shortcut['link_path']) {
      $mlid = $shortcut['mlid'];
      break;
    }
  }

  $link_mode = isset($mlid) ? 'remove' : 'add';

  if ($link_mode == 'add') {
    $query['token'] = drupal_get_token('shortcut-add-link');
    $link_text = shortcut_set_switch_access() ? t('Add to %shortcut_set shortcuts', array('%shortcut_set' => $shortcut_set->title)) : t('Add to shortcuts');
    $link_path = 'admin/config/user-interface/shortcut/' . $shortcut_set->set_name . '/add-link-inline';
  }
  else {
    $query['mlid'] = $mlid;
    $link_text = shortcut_set_switch_access() ? t('Remove from %shortcut_set shortcuts', array('%shortcut_set' => $shortcut_set->title)) : t('Remove from shortcuts');
    $link_path = 'admin/config/user-interface/shortcut/link/' . $mlid . '/delete';
  }

  $link_text = str_replace('<em class="placeholder">', '', $link_text);
  $link_text = str_replace('</em>', '', $link_text);
  $icon = $link_mode == 'add' ? 'uk-icon-plus' : 'uk-icon-minus';

  return array(
    '#prefix' => '<div class="uk-admin-add-or-remove-shortcuts ' . $link_mode . '-shortcut uk-display-inline-block">',
    '#type' => 'link',
    '#title' => '<i class="' . $icon . '"></i>',
    '#href' => $link_path,
    '#options' => array(
      'attributes' => array(
        'data-uk-tooltip' => "{pos:'bottom'}",
        'title' => $link_text,
      ),
      'query' => $query,
      'html' => TRUE,
    ),
    '#suffix' => '</div>',
  );
}
