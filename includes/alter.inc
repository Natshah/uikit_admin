<?php

/**
 * @file
 * Modify structured content arrays.
 *
 * These hooks are called after the content has been assembled in a structured
 * array and may be used for doing processing which requires that the complete
 * content structure has been built.
 *
 * If the theme wishes to act on the rendered HTML of the content rather than
 * the structured content array, it may use this hook to add a #post_render
 * callback. Alternatively, it could also implement hook_preprocess_HOOK().
 *
 * @see drupal_render()
 * @see theme()
 */

use Drupal\Core\Form\FormStateInterface;

/**
 * Implements hook_form_FORM_ID_alter() for Drupal\node\NodeForm.
 */
function uikit_admin_form_node_form_alter(&$form, FormStateInterface $form_state, $form_id) {
  if (isset($form['actions']) && isset($form['actions']['delete'])) {
    $form['actions']['delete']['#attributes']['class'][] = 'uk-button-small';
  }
}

/**
 * Implements hook_form_FORM_ID_alter() for Drupal\system\Form\ThemeAdminForm.
 */
function uikit_admin_form_system_themes_admin_form_alter(&$form, FormStateInterface $form_state, $form_id) {
  // The actions for the system admin theme settings is contained within the
  // details element. We moved it outside of the details element for better
  // user experience.
  $actions = $form['admin_theme']['actions'];
  unset($form['admin_theme']['actions']);
  $form['actions'] = $actions;

  $form['admin_theme']['#open'] = FALSE;
}

/**
 * Implements hook_theme_suggestions_HOOK_alter() for item-list templates.
 */
function uikit_admin_theme_suggestions_item_list_alter(array &$suggestions, array $variables) {
  $list_style = isset($variables['context']) && isset($variables['context']['list_style']) ? $variables['context']['list_style'] : FALSE;

  if ($list_style) {
    $suggestions[] = 'item_list__' . str_replace('-', '_', $list_style);
  }
}

/**
 * Implements hook_theme_suggestions_HOOK_alter() for links templates.
 */
function uikit_admin_theme_suggestions_links_alter(array &$suggestions, array $variables) {
  $classes = isset($variables['attributes']['class']) ? $variables['attributes']['class'] : [];

  if (in_array('operations', $classes)) {
    $suggestions[] = 'links__operations';
  }
}
