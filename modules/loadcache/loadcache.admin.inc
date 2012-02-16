<?php
// $Id$

/**
 * @file
 * Admin pages for reviewing cache performance.
 */

/**
 * Page callback for the loadcache report.
 */
function loadcache_report() {
  $header = array('Type', 'Hits', 'Misses', 'Mismatches');
  $stats = cache_get('loadcache_stats');
  if ($stats) {
    foreach ($stats->data as $type => $stat) {
      array_unshift($stat, $type);
      $rows[] = $stat;
    }
  }
  return theme('table', $header, $rows);
}

/**
 * Page callback for the loadcache mismatch report.
 */
function loadcache_mismatch_report() {
  $header = array('Id', 'Type', 'Caller');
  $index = cache_get('loadcache_mismatch_index');
  if ($index) {
    foreach ($index->data as $id => $mismatch) {
      $mismatch['id'] = l($id, 'admin/reports/loadcache/inspect/' . $mismatch['id']);
      $rows[] = $mismatch;
    }
  }
  return theme('table', $header, $rows);
}

/**
 * Page callback for the loadcache mismatch inspector.
 */
function loadcache_mismatch_item($mismatch) {
  if (module_exists('devel')) {
    return devel_load_object($mismatch->data);
  }
  return "<textarea rows=30 style=\"width: 100%;\">\n". print_r($mismatch->data, TRUE) .'</textarea>';
}
