<?php

/**
 * @file
 * The theme system, which controls the output of the UIkit Admin theme.
 */

/**
 * Implements theme_admin_block().
 */
function uikit_admin_admin_block($variables) {
  $block = $variables['block'];
  $output = '';

  // Don't display the block if it has no content to display.
  if (empty($block['show'])) {
    return $output;
  }

  $output .= '<div class="uk-panel uk-panel-box uk-panel-header uk-margin-bottom">';

  if (!empty($block['title'])) {
    $output .= '<h3 class="uk-panel-title uk-text-bold uk-text-uppercase">' . $block['title'] . '</h3>';
  }

  if (!empty($block['content'])) {
    $output .= '<div class="body">' . $block['content'] . '</div>';
  }
  else {
    $output .= '<div class="description">' . $block['description'] . '</div>';
  }

  $output .= '</div>';

  return $output;
}

/**
 * Implements theme_admin_block_content().
 */
function uikit_admin_admin_block_content($variables) {
  $content = $variables['content'];
  $output = '';

  if (!empty($content)) {
    $classes = 'uk-list uk-list-line uk-margin-remove uk-admin-list';

    if (system_admin_compact_mode()) {
      $classes .= ' uk-admin-list-compact';
    }

    $output .= '<ul class="' . $classes . '">';

    foreach ($content as $item) {
      $item['localized_options']['attributes']['class'][] = 'uk-text-bold';
      $output .= '<li>';

      if (!system_admin_compact_mode()) {
        $output .= '<i class="uk-icon-chevron-circle-right uk-text-muted uk-display-inline-block uk-admin-vertical-align-top" style="margin-top: 2px"></i>';
        $output .= '<div class="uk-margin-left uk-display-inline-block">';
        $output .= l($item['title'], $item['href'], $item['localized_options']);
      }
      else {
        $output .= l($item['title'], $item['href'], $item['localized_options']);
      }

      if (isset($item['description']) && !system_admin_compact_mode()) {
        $output .= '<div class="uk-text-muted">' . filter_xss_admin($item['description']) . '</div>';
      }

      if (!system_admin_compact_mode()) {
        $output .= '</div>';
      }

      $output .= '</li>';
    }

    $output .= '</ul>';
  }
  return $output;
}

/**
 * Implements theme_breadcrumb().
 */
function uikit_admin_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];
  $output = '';

  if (!empty($breadcrumb)) {
    // Provide a navigational heading to give context for breadcrumb links to
    // screen-reader users. Make the heading invisible with .uk-hidden.
    $output .= '<h2 class="uk-hidden">' . t('You are here') . '</h2>';

    $output .= '<ul class="uk-breadcrumb">';

    foreach ($breadcrumb as $crumb) {
      $output .= '<li>' . $crumb . '</li>';
    }

    $output .= '</ul>';
  }

  return $output;
}

/**
 * Implements theme_fieldset().
 */
function uikit_admin_fieldset($variables) {
  $element = $variables['element'];
  $collapsed = $element['#collapsed'];
  element_set_attributes($element, array('id'));
  _form_set_class($element, array('uk-panel', 'uk-panel-box', 'form-wrapper'));
  $id = $element['#attributes']['id'];

  // When viewing the theme settings page for a specific theme, add the
  // .uk-admin-panel-box-light class to theme nested fieldsets.
  if (substr(current_path(), 0, 26) === 'admin/appearance/settings/') {
    $theme_key = arg(3);
    $all_regions = system_region_list($theme_key);

    $theme_settings = array(
      'edit-meta-viewport' => 'edit-meta-viewport',
      'edit-standard-layout' => 'edit-standard-layout',
      'edit-tablet-layout' => 'edit-tablet-layout',
      'edit-mobile-layout' => 'edit-mobile-layout',
      'edit-navbar-container-settings' => 'edit-navbar-container-settings',
      'edit-navbar-margin' => 'edit-navbar-margin',
    );

    foreach ($all_regions as $region_key => $region) {
      $region_id = 'edit-' . str_replace('_', '-', $region_key);

      if (!in_array($region_id, $theme_settings)) {
        $theme_settings[$region_id] = $region_id;
      }
    }

    if (in_array($id, $theme_settings)) {
      $element['#attributes']['class'][] = 'uk-admin-panel-box-light';
    }
  }

  $output = '<div' . drupal_attributes($element['#attributes']) . '>';

  if (!empty($element['#title'])) {
    $output .= '<h3 class="uk-panel-title uk-admin-panel-title-toggle">';
    $toggle_attributes = array(
      'data-uk-toggle' => "{target:'#" . $id . "-toggle'}",
    );

    $output .= '<a' . drupal_attributes($toggle_attributes) . '>' . $element['#title'] . '</a>';
    $output .= '</h3>';
  }

  $content_attribtues = array(
    'id' => $id . '-toggle',
    'class' => array('uk-admin-panel-content-toggle'),
  );

  if ($collapsed) {
    $content_attribtues['class'][] = 'uk-hidden';
    $content_attribtues['aria-hidden'] = 'true';
  }

  $output .= '<div' . drupal_attributes($content_attribtues) . '>';

  if (!empty($element['#description'])) {
    $output .= '<p class="uk-text-muted">' . $element['#description'] . '</p>';
  }

  $output .= $element['#children'];

  if (isset($element['#value'])) {
    $output .= $element['#value'];
  }

  $output .= '</div>';
  $output .= '</div>';
  return $output;
}

/**
 * Implements theme_fieldset().
 */
function uikit_admin_fieldset__non_collapsible($variables) {
  $element = $variables['element'];
  element_set_attributes($element, array('id'));
  _form_set_class($element, array());

  $output = '<div' . drupal_attributes($element['#attributes']) . '>';

  if (!empty($element['#title'])) {
    $output .= '<h2>' . $element['#title'] . '</h2>';
  }

  if (!empty($element['#description'])) {
    $output .= '<div class="uk-text-muted">' . $element['#description'] . '</div>';
  }

  $output .= $element['#children'];

  if (isset($element['#value'])) {
    $output .= $element['#value'];
  }

  $output .= '</div>';
  return $output;
}

/**
 * Implements theme_form_element_label().
 */
function uikit_admin_form_element_label__item($variables) {
  $element = $variables['element'];
  $title = !empty($element['#title']) ? filter_xss_admin($element['#title']) : '';

  if ($title) {
    return '<h3>' . $title . '</h3>';
  }
}

/**
 * Implements theme_menu_local_action().
 */
function uikit_admin_menu_local_action($variables) {
  $link = $variables['element']['#link'];
  $link['localized_options']['attributes']['class'][] = 'uk-button';
  $link['localized_options']['attributes']['class'][] = 'uk-button-primary';
  $output = '<li>';

  if (isset($link['href'])) {
    $output .= l($link['title'], $link['href'], isset($link['localized_options']) ? $link['localized_options'] : array());
  }
  elseif (!empty($link['localized_options']['html'])) {
    $output .= $link['title'];
  }
  else {
    $output .= check_plain($link['title']);
  }

  $output .= '</li>';

  return $output;
}

/**
 * Implements theme_menu_local_task().
 */
function uikit_admin_menu_local_task($variables) {
  $link = $variables['element']['#link'];
  $link_text = $link['title'];

  if (!empty($variables['element']['#active'])) {
    // Add text to indicate active tab for non-visual users.
    $active = '<span class="uk-hidden">' . t('(active tab)') . '</span>';

    // If the link does not contain HTML already, check_plain() it now.
    // After we set 'html'=TRUE the link will not be sanitized by l().
    if (empty($link['localized_options']['html'])) {
      $link['title'] = check_plain($link['title']);
    }

    $link['localized_options']['html'] = TRUE;
    $link_text = t('!local-task-title!active', array('!local-task-title' => $link['title'], '!active' => $active));
  }

  return '<li' . (!empty($variables['element']['#active']) ? ' class="active uk-active"' : '') . '>' . l($link_text, $link['href'], $link['localized_options']) . "</li>\n";
}

/**
 * Implements theme_node_add_list().
 */
function uikit_admin_node_add_list($variables) {
  $content = $variables['content'];

  if ($content) {
    $output = '<ul class="uk-list uk-list-line uk-admin-list">';

    foreach ($content as $item) {
      $item['localized_options']['attributes']['class'][] = 'uk-text-bold';
      $output .= '<li>';
      $output .= '<i class="uk-icon-chevron-circle-right uk-text-muted uk-display-inline-block uk-admin-vertical-align-top" style="margin-top: 2px"></i>';
      $output .= '<div class="uk-margin-left uk-display-inline-block">';
      $output .= l($item['title'], $item['href'], $item['localized_options']);

      if (isset($item['description'])) {
        $output .= '<div class="uk-text-muted">' . filter_xss_admin($item['description']) . '</div>';
      }

      $output .= '</div>';
      $output .= '</li>';
    }

    $output .= '</ul>';
  }
  else {
    $output .= '<p>' . t('You have not created any content types yet. Go to the <a href="@create-content">content type creation page</a> to add a new content type.', array('@create-content' => url('admin/structure/types/add'))) . '</p>';
  }

  return $output;
}

/**
 * Implements theme_system_themes_page().
 */
function uikit_admin_system_themes_page($variables) {
  $theme_groups = $variables['theme_groups'];

  $output = '<div id="system-themes-page">';

  foreach ($variables['theme_group_titles'] as $state => $title) {
    if (!count($theme_groups[$state])) {
      // Skip this group of themes if no theme is there.
      continue;
    }

    $grid = $state == 'disabled' ? ' uk-grid uk-margin' : ' uk-margin-large-bottom';
    $title_width = $state == 'disabled' ? ' class="uk-width-1-1 uk-margin"' : '';

    // Start new theme group.
    $output .= $state == 'disabled' ? '<div class="uk-grid-divider"></div>' : '';
    $output .= '<div class="system-themes-list system-themes-list-' . $state . $grid . '"><h2' . $title_width . '>' . $title . '</h2>';

    foreach ($theme_groups[$state] as $theme) {
      // Localize the theme description.
      $description = t('@description', array('@description' => $theme->info['description']));

      // Style theme info.
      $notes = count($theme->notes) ? ' (' . implode(', ', $theme->notes) . ')' : '';
      $version = isset($theme->info['version']) ? $theme->info['version'] : '';

      if ($state == 'enabled') {
        $screenshot_variables = array(
          'path' => $theme->screenshot['path'],
          'width' => '294',
          'alt' => $theme->screenshot['alt'],
          'title' => $theme->screenshot['title'],
          'attributes' => array(
            'class' => array('screenshot', 'uk-float-left', 'uk-margin-right'),
          ),
        );

        // Theme the screenshot.
        $screenshot = $theme->screenshot ? theme('image', $screenshot_variables) : '<div class="no-screenshot">' . t('no screenshot') . '</div>';

        $theme->classes[] = 'theme-selector';
        $theme->classes[] = 'uk-margin-bottom';
        $theme->classes[] = 'uk-clearfix';
        $theme_default = in_array('theme-default', $theme->classes) ? ' uk-text-bold' : '';
        $output .= '<div class="' . implode(' ', $theme->classes) . '">';
        $output .= $screenshot;
        $output .= '<div class="theme-info">';
        $output .= '<h3 class="uk-margin-bottom-remove' . $theme_default . '">' . $theme->info['name'] . ' ' . $version . $notes . '</h3>';
        $output .= '<div class="theme-description">' . html_entity_decode($description) . '</div>';

        // Make sure to provide feedback on compatibility.
        if (!empty($theme->incompatible_core)) {
          $output .= '<div class="incompatible">' . t('This version is not compatible with Drupal !core_version and should be replaced.', array('!core_version' => DRUPAL_CORE_COMPATIBILITY)) . '</div>';
        }
        elseif (!empty($theme->incompatible_php)) {
          if (substr_count($theme->info['php'], '.') < 2) {
            $theme->info['php'] .= '.*';
          }
          $output .= '<div class="incompatible">' . t('This theme requires PHP version @php_required and is incompatible with PHP version !php_version.', array(
            '@php_required' => $theme->info['php'],
            '!php_version' => phpversion(),
          )) . '</div>';
        }
        else {
          $output .= theme('links', array(
            'links' => $theme->operations,
            'attributes' => array(
              'class' => array(
                'uk-subnav',
                'uk-subnav-line',
                'uk-margin-remove',
                'uk-admin-theme-operations',
              ),
            ),
          ));
        }
        $output .= '</div></div>';
      }
      else {
        $screenshot_variables = array(
          'path' => $theme->screenshot['path'],
          'width' => '194',
          'alt' => $theme->screenshot['alt'],
          'title' => $theme->screenshot['title'],
          'attributes' => array(
            'class' => array('screenshot'),
          ),
        );

        // Theme the screenshot.
        $screenshot = $theme->screenshot ? theme('image', $screenshot_variables) : '<div class="no-screenshot">' . t('no screenshot') . '</div>';

        $theme->classes[] = 'theme-selector';
        $theme->classes[] = 'uk-width-1-3';
        $theme->classes[] = 'uk-margin';
        $output .= '<div class="' . implode(' ', $theme->classes) . '">';
        $output .= $screenshot;
        $output .= '<div class="theme-info uk-margin-top">';
        $output .= '<h3 class="uk-margin-bottom-remove">' . $theme->info['name'] . ' ' . $version . $notes . '</h3>';
        $output .= '<div class="theme-description">' . html_entity_decode($description) . '</div>';

        // Make sure to provide feedback on compatibility.
        if (!empty($theme->incompatible_core)) {
          $output .= '<div class="incompatible">' . t('This version is not compatible with Drupal !core_version and should be replaced.', array('!core_version' => DRUPAL_CORE_COMPATIBILITY)) . '</div>';
        }
        elseif (!empty($theme->incompatible_php)) {
          if (substr_count($theme->info['php'], '.') < 2) {
            $theme->info['php'] .= '.*';
          }
          $output .= '<div class="incompatible">' . t('This theme requires PHP version @php_required and is incompatible with PHP version !php_version.', array(
            '@php_required' => $theme->info['php'],
            '!php_version' => phpversion(),
          )) . '</div>';
        }
        else {
          $output .= theme('links', array(
            'links' => $theme->operations,
            'attributes' => array(
              'class' => array(
                'uk-subnav',
                'uk-subnav-line',
                'uk-margin-remove',
                'uk-admin-theme-operations',
              ),
            ),
          ));
        }
        $output .= '</div></div>';
      }
    }

    $output .= '</div>';
    $output .= $state == 'disabled' ? '<div class="uk-grid-divider"></div>' : '';
  }
  $output .= '</div>';

  return $output;
}

/**
 * Implements theme_tablesort_indicator().
 */
function uikit_admin_tablesort_indicator($variables) {
  $style = $variables['style'];

  if ($style == 'asc') {
    return '<i class="uk-icon-sort-asc tablesort"></i>';
  }
  else {
    return '<i class="uk-icon-sort-desc tablesort"></i>';
  }
}

/**
 * Implements theme_update_report().
 */
function uikit_admin_update_report($variables) {
  $data = $variables['data'];

  $last = variable_get('update_last_check', 0);
  $output = theme('update_last_check', array('last' => $last));

  if (!is_array($data)) {
    $output .= '<p>' . $data . '</p>';
    return $output;
  }

  $header = array();
  $rows = array();

  $notification_level = variable_get('update_notification_threshold', 'all');

  // Create an array of status values keyed by module or theme name, since
  // we'll need this while generating the report if we have to cross reference
  // anything (e.g. subthemes which have base themes missing an update).
  foreach ($data as $project) {
    foreach ($project['includes'] as $key => $name) {
      $status[$key] = $project['status'];
    }
  }

  foreach ($data as $project) {
    switch ($project['status']) {
      case UPDATE_CURRENT:
        $class = 'success';
        $icon = 'check';
        break;

      case UPDATE_UNKNOWN:
      case UPDATE_FETCH_PENDING:
      case UPDATE_NOT_FETCHED:
        $class = 'warning';
        $icon = 'question-circle';
        break;

      case UPDATE_NOT_SECURE:
      case UPDATE_REVOKED:
      case UPDATE_NOT_SUPPORTED:
        $class = 'danger';
        $icon = 'exclamation-circle';
        break;

      case UPDATE_NOT_CHECKED:
      case UPDATE_NOT_CURRENT:
      default:
        $class = 'warning';
        $icon = 'exclamation-triangle';
        break;
    }

    $row = '<div class="version-status uk-float-right">';
    $status_label = theme('update_status_label', array('status' => $project['status']));
    $row .= !empty($status_label) ? $status_label : check_plain($project['reason']);
    $row .= '<i class="uk-icon-' . $icon . ' uk-text-' . $class . '"></i>';
    $row .= '</div>';

    $row .= '<div class="project uk-text-bold uk-admin-text-dark">';
    if (isset($project['title'])) {
      if (isset($project['link'])) {
        $row .= l($project['title'], $project['link']);
      }
      else {
        $row .= check_plain($project['title']);
      }
    }
    else {
      $row .= check_plain($project['name']);
    }
    $row .= ' ' . check_plain($project['existing_version']);
    if ($project['install_type'] == 'dev' && !empty($project['datestamp'])) {
      $row .= ' <span class="version-date uk-admin-text-weight-normal">(' . format_date($project['datestamp'], 'custom', 'F j, Y') . ')</span>';
    }
    $row .= '</div>';

    $versions_inner = '';
    $security_class = array();
    $version_class = array();
    if (isset($project['recommended'])) {
      if ($project['status'] != UPDATE_CURRENT || $project['existing_version'] !== $project['recommended']) {

        // First, figure out what to recommend.
        // If there's only 1 security update and it has the same version we're
        // recommending, give it the same CSS class as if it was recommended,
        // but don't print out a separate "Recommended" line for this project.
        if (!empty($project['security updates']) && count($project['security updates']) == 1 && $project['security updates'][0]['version'] === $project['recommended']) {
          $security_class[] = 'version-recommended';
          $security_class[] = 'version-recommended-strong';
        }
        else {
          $version_class[] = 'version-recommended';
          // Apply an extra class if we're displaying both a recommended
          // version and anything else for an extra visual hint.
          if ($project['recommended'] !== $project['latest_version']
            || !empty($project['also'])
            || ($project['install_type'] == 'dev'
              && isset($project['dev_version'])
              && $project['latest_version'] !== $project['dev_version']
              && $project['recommended'] !== $project['dev_version'])
            || (isset($project['security updates'][0])
              && $project['recommended'] !== $project['security updates'][0])
          ) {
            $version_class[] = 'version-recommended-strong';
          }
          $versions_inner .= theme('update_version', array(
            'version' => $project['releases'][$project['recommended']],
            'tag' => t('Recommended version:'),
            'class' => $version_class,
          ));
        }

        // Now, print any security updates.
        if (!empty($project['security updates'])) {
          $security_class[] = 'version-security';
          foreach ($project['security updates'] as $security_update) {
            $versions_inner .= theme('update_version', array(
              'version' => $security_update,
              'tag' => t('Security update:'),
              'class' => $security_class,
            ));
          }
        }
      }

      if ($project['recommended'] !== $project['latest_version']) {
        $versions_inner .= theme('update_version', array(
          'version' => $project['releases'][$project['latest_version']],
          'tag' => t('Latest version:'),
          'class' => array('version-latest'),
        ));
      }
      if ($project['install_type'] == 'dev'
        && $project['status'] != UPDATE_CURRENT
        && isset($project['dev_version'])
        && $project['recommended'] !== $project['dev_version']) {
        $versions_inner .= theme('update_version', array(
          'version' => $project['releases'][$project['dev_version']],
          'tag' => t('Development version:'),
          'class' => array('version-latest'),
        ));
      }
    }

    if (isset($project['also'])) {
      foreach ($project['also'] as $also) {
        $versions_inner .= theme('update_version', array(
          'version' => $project['releases'][$also],
          'tag' => t('Also available:'),
          'class' => array('version-also-available'),
        ));
      }
    }

    if (!empty($versions_inner)) {
      $row .= '<div class="versions">' . $versions_inner . '</div>';
    }
    $row .= '<div class="info">';
    if (!empty($project['extra'])) {
      $row .= '<div class="extra">';
      foreach ($project['extra'] as $key => $value) {
        $row .= '<div class="' . implode(' ', $value['class']) . '">';
        $row .= check_plain($value['label']) . ': ';
        $row .= drupal_placeholder($value['data']);
        $row .= '</div>';
      }
      $row .= '</div>';
    }

    $row .= '<div class="includes uk-margin-top">';
    sort($project['includes']);
    if (!empty($project['disabled'])) {
      sort($project['disabled']);
      // Make sure we start with a clean slate for each project in the report.
      $includes_items = array();
      $row .= t('Includes:');
      $includes_items[] = t('Enabled: %includes', array('%includes' => implode(', ', $project['includes'])));
      $includes_items[] = t('Disabled: %disabled', array('%disabled' => implode(', ', $project['disabled'])));
      $row .= theme('item_list', array('items' => $includes_items));
    }
    else {
      $includes = t('Includes: %includes', array('%includes' => implode(', ', $project['includes'])));
      $includes = str_replace('class="placeholder"', 'class="placeholder uk-text-' . $class . '"', $includes);
      $row .= $includes;
    }
    $row .= '</div>';

    if (!empty($project['base_themes'])) {
      $row .= '<div class="basethemes">';
      asort($project['base_themes']);
      $base_themes = array();
      foreach ($project['base_themes'] as $base_key => $base_theme) {
        switch ($status[$base_key]) {
          case UPDATE_NOT_SECURE:
          case UPDATE_REVOKED:
          case UPDATE_NOT_SUPPORTED:
            $base_themes[] = t('%base_theme (!base_label)', array(
              '%base_theme' => $base_theme,
              '!base_label' => theme('update_status_label', array(
                'status' => $status[$base_key],
              )),
            ));
            break;

          default:
            $base_themes[] = drupal_placeholder($base_theme);
        }
      }
      $row .= t('Depends on: !basethemes', array('!basethemes' => implode(', ', $base_themes)));
      $row .= '</div>';
    }

    if (!empty($project['sub_themes'])) {
      $row .= '<div class="subthemes">';
      sort($project['sub_themes']);
      $row .= t('Required by: %subthemes', array('%subthemes' => implode(', ', $project['sub_themes'])));
      $row .= '</div>';
    }

    $row .= '</div>';

    if (!isset($rows[$project['project_type']])) {
      $rows[$project['project_type']] = array();
    }
    $row_key = isset($project['title']) ? drupal_strtolower($project['title']) : drupal_strtolower($project['name']);
    $rows[$project['project_type']][$row_key] = array(
      'class' => array('uk-alert', 'uk-alert-' . $class),
      'data' => array($row),
    );
  }

  $project_types = array(
    'core' => t('Drupal core'),
    'module' => t('Modules'),
    'theme' => t('Themes'),
    'module-disabled' => t('Disabled modules'),
    'theme-disabled' => t('Disabled themes'),
  );
  foreach ($project_types as $type_name => $type_label) {
    if (!empty($rows[$type_name])) {
      ksort($rows[$type_name]);
      $output .= '<h3 class="uk-text-bold">' . $type_label . '</h3>';
      $output .= theme('table', array(
        'header' => $header,
        'rows' => $rows[$type_name],
        'attributes' => array('class' => array('update')),
      ));
    }
  }
  return $output;
}

/**
 * Implements theme_update_status_label().
 */
function uikit_admin_update_status_label($variables) {
  switch ($variables['status']) {
    case UPDATE_NOT_SECURE:
      return '<span class="uk-margin-right uk-admin-text-dark">' . t('Security update required!') . '</span>';

    case UPDATE_REVOKED:
      return '<span class="uk-margin-right uk-admin-text-dark">' . t('Revoked!') . '</span>';

    case UPDATE_NOT_SUPPORTED:
      return '<span class="uk-margin-right uk-admin-text-dark">' . t('Not supported!') . '</span>';

    case UPDATE_NOT_CURRENT:
      return '<span class="uk-margin-right uk-admin-text-dark">' . t('Update available') . '</span>';

    case UPDATE_CURRENT:
      return '<span class="uk-margin-right uk-admin-text-dark">' . t('Up to date') . '</span>';

  }
}

/**
 * Implements theme_update_version().
 */
function uikit_admin_update_version($variables) {
  $version = $variables['version'];
  $tag = $variables['tag'];
  $class = implode(' ', $variables['class']);

  $output = '';
  $output .= '<div class="version ' . $class . ' uk-margin-top uk-margin-bottom">';
  $output .= '<div class="version-title uk-display-inline-block">' . $tag . '</div>';
  $output .= '<div class="version-details uk-display-inline-block uk-margin-large-left">';
  $output .= l($version['version'], $version['release_link']);
  $output .= ' <span class="version-date">(' . format_date($version['date'], 'custom', 'F j, Y') . ')</span>';
  $output .= '</div>';
  $output .= '<div class="version-links uk-float-right">';
  $links = array();
  $links['update-download'] = array(
    'title' => t('Download'),
    'href' => $version['download_link'],
  );
  $links['update-release-notes'] = array(
    'title' => t('Release notes'),
    'href' => $version['release_link'],
  );
  $attributes = array(
    'class' => array('uk-list'),
  );
  $output .= theme('links__update_version', array('links' => $links, 'attributes' => $attributes));
  $output .= '</div>';
  $output .= '</div>';
  return $output;
}
